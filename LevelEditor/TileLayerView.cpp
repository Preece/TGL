#include "TileLayerView.h"

TileLayerView::TileLayerView()
{
    widthInTiles = 0;
    heightInTiles = 0;

    resourceManager = NULL;
    layerID = 0;
}

TileLayerView::~TileLayerView()
{
    DestroyAllItems();
}

void TileLayerView::SetLayerSize(int w, int h)
{
    widthInTiles = w;
    heightInTiles = h;
}

void TileLayerView::ToggleVisibility(bool visible)
{
    if(visible)
        show();
    else
        hide();
}

void TileLayerView::DestroyAllItems()
{
    QList<QGraphicsItem*> children = this->children();

    for(int i = 0; i < children.count(); i++)
    {
        if(children[i])
            delete children[i];
    }

    items.clear();

    //previews are children, they have already been deleted
    previewItems.clear();
}

void TileLayerView::RepopulateTiles()
{
    //the strategy is to loop through all the items in the scene,
    //comparing them against the model and updating them accordingly.
    //all tiles that are synchronized in this was are flagged.
    //then, loop through all the tiles in the model, comparing them
    //against the scene items, skipping any flagged ones.
    //this ensures that additions/deletions from the model are 
    //present in the scene

    QList<TileCoord> inspectedItems;
    QHash<TileCoord, TileWidgetItem*>::iterator itemIterator = items.begin();

    //loop through every item in the *scene*
    while(itemIterator != items.end())
    {
        TileWidgetItem *tempItem = itemIterator.value();
        TileCoord itemPos = tempItem->GetPosition();
        TileCoord modelTileOrigin = GetTileOrigin(itemPos.first, itemPos.second);

        //if the items tile origin in the model does not match the tile origin on the scene
        if(modelTileOrigin != tempItem->GetTileOrigin())
        {
            //update the tile to be in line with the model. If the tile doesn't
            //exist in the model, modelTileOrigin will be -1,-1, and this
            //function is smart enough to simply delete that tile and move on
            ModifyTileWidgetItem(itemPos.first, itemPos.second, modelTileOrigin);
        }

        //make note of the fact that the tile at this position has been inspected
        inspectedItems.insert(itemPos);

        ++itemIterator;
    }

    //now loop through every tile in the *model*
    int tileCount = resourceManager->GetTileCount(layerID);

    for(int i = 0; i < tileCount; i++)
    {
        Tile *tempTile = resourceManager->GetTileByIndex(layerID, i);

        //skip any items that were previously inspected
        if(inspectedItems.contains(tempTile->pos))
            continue;
    
        //if we got here, there is a discrepancy between the model and the scene.
        //This function should resolve it        
        ModifyTileWidgetItem(tempTile->pos.first, tempTile->pos.second, tempTile->origin);
    }
}

void TileLayerView::ModifyTileItem(int x, int y, TileCoord newOrigin)
{
    //bounds check    
    if(x >= widthInTiles)
        x = widthInTiles - 1;

    if(y >= heightInTiles)
        y = heightInTiles - 1;

    if(x < 0)
        x = 0;

    if(y < 0)
        y = 0;


    //add a new one
    ModifyTileWidgetItem(x, y, newOrigin);

    //add the new tile into the model through the resource manager
    resourceManager->ModifyTile(layerID, x, y, newOrigin);

}

void TileLayerView::PreviewModifyTile(int x, int y, TileCoord newOrigin)
{
    //bounds check
    if(x >= widthInTiles)
        x = widthInTiles - 1;

    if(y >= heightInTiles)
        y = heightInTiles - 1;

    if(x < 0)
        x = 0;

    if(y < 0)
        y = 0;

    TileWidgetItem *tempTile = new TileWidgetItem;

    //update its Pixmap
    tempTile->SetTilePixmap(resourceManager->GetTilePixmap(newOrigin));

    //set the position
    tempTile->setPos(x * resourceManager->GetLevelProperties()->GetTileWidth(),
                     y * resourceManager->GetLevelProperties()->GetTileHeight());

    previewItems.append(tempTile);
    tempTile->setParentItem(this);
}

//this is a convenience function for adding the graphical element to represent a tile.
//it does not change the model
void TileLayerView::ModifyTileWidgetItem(int x, int y, TileCoord newOrigin)
{
    if(items.value(TileCoord(x, y)))
    {
        //if the right tile is already here, just bail
        if(items[TileCoord(x, y)]->GetTileOrigin() == newOrigin)
            return;
        else
            delete items[TileCoord(x, y)];

        //if they passed in a null tile as the new origin, just bail,
        //its been deleted
        if(newOrigin == TileCoord(-1, -1))
            return;
    }

    TileWidgetItem *tempTileItem = new TileWidgetItem;

    //store the tile origin coordinates in the item
    tempTileItem->SetTileOrigin(newOrigin);

    //update its Pixmap
    tempTileItem->SetTilePixmap(resourceManager->GetTilePixmap(newOrigin));

    int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
    int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

    //set the position
    tempTileItem->setPos(x * tileW, y * tileH);

    //put the new tile item into the map, with the position as the key
    items[TileCoord(x, y)] = tempTileItem;
    tempTileItem->setParentItem(this);
}

void TileLayerView::ClearPreview()
{
    for(int i = 0; i < previewItems.count(); i++)
    {
        if(previewItems[i])
        {
            delete previewItems[i];
            previewItems[i] = NULL;
        }
    }

    previewItems.clear();
}

TileCoord TileLayerView::GetTileOrigin(int x, int y)
{
    return resourceManager->GetTileOrigin(layerID, x, y);
}
