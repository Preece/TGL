#include "TileLayerView.h"

TileLayerView::TileLayerView()
{
    width = 0;
    height = 0;
}

TileLayerView::~TileLayerView()
{
    DestroyAllItems();
}

void TileLayerView::AddTileWidgetItem(Tile *newTile)
{
    if(newTile == NULL)
        return;

    TileWidgetItem *tempTileItem = new TileWidgetItem;

    int tileW, tileH;
    tileW = resourceManager->GetLevelProperties()->GetTileWidth();
    tileH = resourceManager->GetLevelProperties()->GetTileHeight();

    //get the tile and set it as the tileinstance for the item
    tempTileItem->SetTile(newTile);

    //update its Pixmap
    tempTileItem->SetTilePixmap(resourceManager->GetTilePixmap(newTile->originX, newTile->originY));

    //set the position
    tempTileItem->setPos(newTile->x * tileW, newTile->y * tileH);

    items.append(tempTileItem);
    tempTileItem->setParentItem(this);
}

void TileLayerView::SetLayerSize(int w, int h)
{
    width = w;
    height = h;
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
    for(int i = 0; i < items.count(); i++)
    {
        delete items[i];
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
    for(int i = 0; i < items.count(); i++)
    {
        if(items[i])
            delete items[i];

        items[i] = NULL;
    }

    items.clear();

    layer->ResetIterator();

    //loop through all the tile instances in the model
    for(int i = 0; i < layer->GetTileCount(); i++)
    {
        //if the tile we want is valid
        if(layer->GetTileFromIterator() != 0)
        {
            AddTileWidgetItem(layer->GetTileFromIterator());
        }

        //advance the iterator
        layer->AdvanceIterator();
    }
}

void TileLayerView::ModifyTile(int x, int y, TileCoord newOrigin)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return;

    Tile *tempTile = layer->GetTileAtPos(x, y);

    //if there is not a tile at this position
    if(tempTile == 0)
    {
        //add a new one
        AddTileWidgetItem(layer->AddTile(x, y, newOrigin.first, newOrigin.second));
    }
    //if a tile already exists at this position
    else
    {
        //modify the tile origin values
        tempTile->originX = newOrigin.first;
        tempTile->originY = newOrigin.second;

        //and change its pixmap
        //THIS IS NOT FINAL. WAY TOO INEFFICIENT. USE ANOTHER QMAP FOR THE TILEWIDGETITEMS
        RepopulateTiles();
    }
}

void TileLayerView::PreviewModifyTile(int x, int y, TileCoord newOrigin)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return;

    TileWidgetItem *tempTile = new TileWidgetItem;

    //update its Pixmap
    tempTile->SetTilePixmap(resourceManager->GetTilePixmap(newOrigin.first, newOrigin.second));

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

TileWidgetItem *TileLayerView::GetTileWidgetItem(int x, int y)
{
    for(int i = 0; i < items.count(); i++)
    {
        if(items[i]->GetTile()->x == x && items[i]->GetTile()->y == y)
            return items[i];
    }

    return NULL;
}

TileCoord TileLayerView::GetTileOrigin(int x, int y)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return TileCoord(-1, -1);

    return layer->GetTileOrigin(x, y);
}
