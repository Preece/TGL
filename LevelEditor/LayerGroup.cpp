#include "LayerGroup.h"

LayerGroup::LayerGroup()
{
    width = 0;
    height = 0;
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

        //simulation of 2D array. Refill the items list.
        items[(w * x) + y] = tempList[j];
    }
}

void LayerGroup::ToggleVisibility(bool visible)
{
    if(visible)
        show();
    else
        hide();
}

void LayerGroup::ModifyTile(int x, int y, int newType)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return;

    int pos = (x * width) + y;

    //if there is not a tile at this position
    if(items[pos] == NULL && newType != NULL)
    {
        TileInstanceItem *tempTile = new TileInstanceItem;

        //add a tile to the model, and set it as the tileinstance for the item
        tempTile->SetTileInstance(layer->AddTile(x, y, newType));

        int tileID = tempTile->GetTileInstance()->GetTileID();


        //update its Pixmap
        tempTile->SetTilePixmap(resourceManager->GetTilePixmap(tileID));

        //set the position
        tempTile->setPos(x * resourceManager->GetLevelProperties()->GetTileWidth(),
                         y * resourceManager->GetLevelProperties()->GetTileHeight());

        items[pos] = tempTile;
        addToGroup(tempTile);
    }
    //if a tile already exists at this position
    else
    {
        //and the new type is not 0
        if(newType != NULL)
        {
            //modify the Tile ID it references
            items[pos]->GetTileInstance()->SetTileID(newType);

            int tileID = items[pos]->GetTileInstance()->GetTileID();

            //update its Pixmap
            items[pos]->SetTilePixmap(resourceManager->GetTilePixmap(tileID));
        }
        //if the new type is 0
        else
        {
            //delete the tile and remove it from the layer model
            int oldID = items[pos]->GetTileInstance()->GetID();
            layer->RemoveChild(oldID);

            delete items[pos];
            items[pos] = NULL;
        }
    }
}

int LayerGroup::GetTileType(int x, int y)
{
    //bounds check
    if(x >= width || y >= height || x < 0 || y < 0)
        return 0;

    int pos = (x * width) + y;

    TileInstanceItem *tempItem = items[pos];
    int tileID = tempItem->GetTileID();

    if(tempItem == NULL)
        return 0;
    else
        return tileID;
}
