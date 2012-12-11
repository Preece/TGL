#include "Layer.h"

Layer::Layer()
{
    width = 0;
    height = 0;
}

bool Layer::SaveToFile(Exporter *exporter)
{
    return false;
}

bool Layer::LoadFromFile(Exporter *exporter)
{
    return false;
}

void Layer::ModifyTile(int x, int y, int ID)
{
    //check that the location is in bounds
    if(x >= width || y >= height || x < 0 || y < 0)
        return;

    //get the tile instance at the specified position
    TileInstance *tempTile = GetTileAtPosition(x, y);

    //if it exists
    if(tempTile)
    {
        //and the ID is not zero
        if(ID != 0)
        {
            //modify its ID
            tempTile->SetTileID(ID);
        }
        //if the ID is 0
        else if(ID == 0)
        {
            //remove it because a 0 ID means it is blank
            RemoveChild(tempTile->GetID());
            tiles[x][y] = NULL;
        }
    }
    //if the tile does not exist and the ID is not zero
    else if(ID != 0)
    {
        //create a new tile instance
        tempTile = new TileInstance;

        //set its properties
        tempTile->SetX(x);
        tempTile->SetY(y);
        tempTile->SetTileID(ID);

        //and add it to the child list, and the tile grid
        AddChild(tempTile);
        tiles[x][y] = tempTile;
    }
}

int Layer::GetTileType(int x, int y)
{
    if(x < width && y < height && x >= 0 && y >= 0)
        return tiles[x][y]->GetTileID();

    return 0;

}

TileInstance *Layer::GetTileAtIndex(int index)
{
    if(index < 0 || index >= GetChildCount())
        return NULL;

    return static_cast<TileInstance*>(GetChildByIndex(index));
}

TileInstance *Layer::GetTileAtPosition(int x, int y)
{
    if(x < width && y < height && x >= 0 && y >= 0)
        return tiles[x][y];

    return NULL;
}

void Layer::SetLayerSize(int w, int h)
{
    width = w;
    height = h;

    //clear out the tile list
    tiles.clear();

    QList<TileInstance*> tempList;

    //pad it with all NULLs
    for(int i = 0; i < w; i++)
    {
        tempList.clear();

        for(int j = 0; j < h; j++)
        {
            tempList.append(NULL);
        }

        tiles.append(tempList);
    }

    TileInstance *tempTile;

    //loop through the list of children and add them at the correct spot
    for(int i = 0; i < GetChildCount(); i++)
    {
        tempTile = static_cast<TileInstance*>(GetChildByIndex(i));

        int x = tempTile->GetX();
        int y = tempTile->GetY();

        if(x < w && y < h)
            tiles[x][y] = tempTile;
    }
}
