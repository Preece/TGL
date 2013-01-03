#include "LayerGroup.h"

LayerGroup::LayerGroup()
{
    width = 0;
    height = 0;
}

LayerGroup::~LayerGroup()
{
    DestroyAllItems();
}

void LayerGroup::SetLayerSize(int w, int h)
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

void LayerGroup::AddObjectItem(ObjectInstanceItem *newObj)
{
    if(newObj)
    {
        objects.append(newObj);
        newObj->setParentItem(this);
    }
}

void LayerGroup::ToggleVisibility(bool visible)
{
    if(visible)
        show();
    else
        hide();
}

void LayerGroup::DestroyAllItems()
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

void LayerGroup::RepopulateTiles()
{
    //clear out all the tiles
    for(int i = 0; i < items.count(); i++)
    {
        if(items[i])
            delete items[i];

        items[i] = NULL;
    }

    items.clear();

    //loop through all the tile instances in the model
    for(int i = 0; i < layer->GetTileCount(); i++)
    {
        TileInstanceItem *tempTile = new TileInstanceItem;

        //get the tile and set it as the tileinstance for the item
        tempTile->SetTileInstance(layer->GetTileAtIndex(i));

        int tileID = tempTile->GetTileInstance()->GetTileID();

        //update its Pixmap
        tempTile->SetTilePixmap(resourceManager->GetTilePixmap(tileID));

        //set the position
        tempTile->setPos(tempTile->GetTileInstance()->GetX() * resourceManager->GetLevelProperties()->GetTileWidth(),
                         tempTile->GetTileInstance()->GetY() * resourceManager->GetLevelProperties()->GetTileHeight());

        items.append(tempTile);
        tempTile->setParentItem(this);
    }
}

void LayerGroup::RepopulateObjects()
{
}

void LayerGroup::ModifyTile(int x, int y, int newType)
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

void LayerGroup::PreviewModifyTile(int x, int y, int newType)
{
    TileInstanceItem *tempTile = new TileInstanceItem;

    //update its Pixmap
    tempTile->SetTilePixmap(resourceManager->GetTilePixmap(newType));

    //set the position
    tempTile->setPos(x * resourceManager->GetLevelProperties()->GetTileWidth(),
                     y * resourceManager->GetLevelProperties()->GetTileHeight());

    previewItems.append(tempTile);
    tempTile->setParentItem(this);
}

void LayerGroup::ClearPreview()
{
    for(int i = 0; i < previewItems.count(); i++)
    {
        delete previewItems[i];
    }

    previewItems.clear();
}

TileInstanceItem *LayerGroup::GetTileInstanceItem(int x, int y)
{
    for(int i = 0; i < items.count(); i++)
    {
        if(items[i]->GetTileInstance()->GetX() == x && items[i]->GetTileInstance()->GetY() == y)
            return items[i];
    }

    return NULL;
}

int LayerGroup::GetTileType(int x, int y)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return 0;

    return layer->GetTileType(x, y);
}
