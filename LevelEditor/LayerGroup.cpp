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

    //store the current list away
    QList<TileInstanceItem*> tempList = items;

    //clear out the current list
    items.clear();

    //build out the tiles array to be the correct size
    for(int i = 0; i < (w*h); i++)
    {
        //fill it with NULL pointers
        items.append(NULL);
    }

    int x = 0;
    int y = 0;

    //loop through the stored list
    for(int j = 0; j < tempList.count(); j++)
    {
        //place each item from the temp list into the correct spot
        x = tempList[j]->GetX();
        y = tempList[j]->GetY();

        if(tempList[j])
        {
            //simulation of 2D array. Refill the items list.
            items[(w * x) + y] = tempList[j];
        }
        else
            items[(w * x) + y] = NULL;
    }
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

    //loop through all the tile instances in the model
    for(int i = 0; i < layer->GetTileCount(); i++)
    {
        //add the tile instance to the group
        TileInstanceItem *tempTile = new TileInstanceItem;

        tempTile->SetTileInstance(layer->GetTileAtIndex(i));

        int tileID = tempTile->GetTileInstance()->GetTileID();

        //update its Pixmap
        tempTile->SetTilePixmap(resourceManager->GetTilePixmap(tileID));

        //set the position
        tempTile->setPos(tempTile->GetTileInstance()->GetX() * resourceManager->GetLevelProperties()->GetTileWidth(),
                         tempTile->GetTileInstance()->GetY() * resourceManager->GetLevelProperties()->GetTileHeight());

        int pos = (tempTile->GetTileInstance()->GetX() * resourceManager->GetLevelProperties()->GetTileWidth()) + tempTile->GetTileInstance()->GetX();
        items[pos] = tempTile;
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

    int pos = (x * width) + y;

    //if there is not a tile at this position
    if(items[pos] == NULL && newType != 0)
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

        items[pos] = tempTile;
        tempTile->setParentItem(this);
    }
    //if a tile already exists at this position
    else
    {
        int oldID = items[pos]->GetTileID();

        //and the new type is not 0
        if(newType != 0 && oldID != newType)
        {
            resourceManager->ModifyTileInstance(layer, x, y, newType, oldID);

            int tileID = items[pos]->GetTileInstance()->GetTileID();

            //update its Pixmap
            items[pos]->SetTilePixmap(resourceManager->GetTilePixmap(tileID));
        }
        //if the new type is 0
        else if(newType == 0)
        {
            //delete the tile and remove it from the layer model
            int oldID = items[pos]->GetTileInstance()->GetID();
            layer->RemoveChild(oldID);

            delete items[pos];
            items[pos] = NULL;
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

int LayerGroup::GetTileType(int x, int y)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return 0;

    int pos = (x * width) + y;

    TileInstanceItem *tempItem = items[pos];

    if(tempItem == NULL)
        return 0;
    else
        return tempItem->GetTileID();
}
