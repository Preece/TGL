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
    //clear out all the tiles
    DestroyAllItems();

    //build and add all tile widget items from the model
    for(int i = 0; i < resourceManager->GetTileCount(layerID); i++)
    {
        Tile *tempTile = resourceManager->GetTileByIndex(layerID, i);

        if(tempTile)
            AddTileWidgetItem(tempTile->pos.first, tempTile->pos.second, tempTile->origin);
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

    //if there is not a tile at this position in the model
    if(resourceManager->GetTileOrigin(layerID, x, y) == TileCoord(-1, -1))
    {
        //add a new one
        AddTileWidgetItem(x, y, newOrigin);

        //add the new tile into the model through the resource manager
        resourceManager->ModifyTile(layerID, x, y, newOrigin, TileCoord(-1, -1));
    }
    else
    {
        //modify the tile origin values in the model
        resourceManager->ModifyTile(layerID, x, y, newOrigin, resourceManager->GetTileOrigin(layerID, x, y));

        //get the visible tile widget
        TileWidgetItem *tempTileItem = items[TileCoord(x, y)];

        //and update its pixmap
        if(tempTileItem)
            tempTileItem->SetTilePixmap(resourceManager->GetTilePixmap(newOrigin));

    }
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
void TileLayerView::AddTileWidgetItem(int x, int y, TileCoord newOrigin)
{
    if(items.value(TileCoord(x, y)))
        return;

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
    //bounds check
    if(x >= widthInTiles || y >= heightInTiles || x < 0 || y < 0)
        return TileCoord(-1, -1);

    return resourceManager->GetTileOrigin(layerID, x, y);
}
