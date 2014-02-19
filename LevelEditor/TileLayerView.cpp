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

void TileLayerView::SetLayerSize(int w, int h)
{
    //if the new size is the same as the current size
    if(width == w && height == h)
    {
        //nothing needs to be done
        return;
    }

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
        TileWidgetItem *tempTile = new TileWidgetItem;

        //if the tile we want is valid
        if(layer->GetTileFromIterator() != 0)
        {
            //get the tile and set it as the tileinstance for the item
            tempTile->SetTile(layer->GetTileFromIterator());

            //update its Pixmap
            tempTile->SetTilePixmap(resourceManager->GetTilePixmap(tileID));

            //set the position
            tempTile->setPos(tempTile->GetTileInstance()->GetX() * resourceManager->GetLevelProperties()->GetTileWidth(),
                            tempTile->GetTileInstance()->GetY() * resourceManager->GetLevelProperties()->GetTileHeight());

            items.append(tempTile);
            tempTile->setParentItem(this);
        }

        //advance the iterator
        layer->AdvanceIterator();
    }
}

void TileLayerView::RepopulateObjects()
{
}

void TileLayerView::ModifyTile(int x, int y, int newType)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return;

    int oldType = layer->GetTileType(x, y);
    //if there is not a tile at this position
    if(oldType == 0 && newType != 0)
    {
        TileInstanceItem *tempTile = new TileInstanceItem;

        //add a tile to the model, and set it as the tileinstance for the item
        tempTile->SetTileInstance(resourceManager->AddTileInstance(layer, x, y, newType));

        int tileID = tempTile->GetTileInstance()->GetTileID();

        //update its Pixmap
        tempTile->SetTilePixmap(resourceManager->GetTilePixmap(tileID));

        //set the position
        tempTile->setPos(x * resourceManager->GetLevelProperties()->GetTileWidth(),
                         y * resourceManager->GetLevelProperties()->GetTileHeight());

        items.append(tempTile);
        tempTile->setParentItem(this);
    }
    //if a tile already exists at this position
    else
    {
        //and the new type is not 0
        if(newType != 0 && oldType != newType)
        {
            resourceManager->ModifyTileInstance(layer, x, y, newType, oldType);

            //update its Pixmap
            GetTileInstanceItem(x, y)->SetTilePixmap(resourceManager->GetTilePixmap(newType));
        }
        //if the new type is 0
        else if(newType == 0)
        {
            //delete the tile and remove it from the layer model
            //int oldID = items[pos]->GetTileInstance()->GetID();
            //layer->RemoveChild(oldID);

            //delete items[pos];
            //items[pos] = NULL;
        }
    }
}

void TileLayerView::PreviewModifyTile(int x, int y, int newType)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return;

    TileInstanceItem *tempTile = new TileInstanceItem;

    //update its Pixmap
    tempTile->SetTilePixmap(resourceManager->GetTilePixmap(newType));

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

TileInstanceItem *TileLayerView::GetTileInstanceItem(int x, int y)
{
    for(int i = 0; i < items.count(); i++)
    {
        if(items[i]->GetTileInstance()->GetX() == x && items[i]->GetTileInstance()->GetY() == y)
            return items[i];
    }

    return NULL;
}

int TileLayerView::GetTileType(int x, int y)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return 0;

    return layer->GetTileType(x, y);
}
