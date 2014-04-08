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

void TileLayerView::AddTileWidgetItem(Tile *newTile)
{
    if(newTile == NULL)
        return;


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

bool TileLayerView::IsVisible()
{
    return IsVisible();
}

void TileLayerView::DestroyAllItems()
{
    //iterate through all elements in the map, and delete the tilewidgets
    QMap<TileCoord, TileWidgetItem*>::const_iterator i = items.constBegin();

    while (i != items.constEnd())
    {
        if(i.value())
            delete i.value();

        ++i;
    }

    items.clear();

    for(int i = 0; i < previewItems.count(); i++)
    {
        delete previewItems[i];
    }

    previewItems.clear();
}

void TileLayerView::RepopulateTiles()
{
    //clear out all the tiles
    DestroyAllItems();

    //build and add all tile widget items from the model

}

void TileLayerView::ModifyTile(int x, int y, TileCoord newOrigin)
{
    //bounds check
    if(x >= widthInTiles || y >= heightInTiles || x < 0 || y < 0)
        return;

    //if there is not a tile at this position
    if(resourceManager->GetTileOrigin(layerID, x, y) == TileCoord(-1, -1))
    {
        //add a new one
        TileWidgetItem *tempTileItem = new TileWidgetItem;

        int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
        int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

        //get the tile and set it as the tileinstance for the item
        tempTileItem->SetTileOrigin(newOrigin);

        //update its Pixmap
        tempTileItem->SetTilePixmap(resourceManager->GetTilePixmap(newOrigin));

        //set the position
        tempTileItem->setPos(x * tileW, y * tileH);

        //put the new tile item into the map, with the new tiles position as the key
        items[TileCoord(x, y)] = tempTileItem;
        tempTileItem->setParentItem(this);
    }
    //if a tile already exists at this position
    else
    {
        //modify the tile origin values in the model
        resourceManager->ModifyTile(layerID, x, y, newOrigin);

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
    if(x >= widthInTiles || y >= heightInTiles || x < 0 || y < 0)
        return;

    TileWidgetItem *tempTile = new TileWidgetItem;

    //update its Pixmap
    tempTile->SetTilePixmap(resourceManager->GetTilePixmap(newOrigin));

    //set the position
    tempTile->setPos(x * resourceManager->GetLevelProperties()->GetTileWidth(),
                     y * resourceManager->GetLevelProperties()->GetTileHeight());

    previewItems.append(tempTile);
    tempTile->setParentItem(this);
}

void TileLayerView::ClearPreview()
{
    for(int i = 0; i < previewItems.count(); i++)
    {
        delete previewItems[i];
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
