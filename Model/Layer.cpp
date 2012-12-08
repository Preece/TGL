#include "Layer.h"

Layer::Layer()
{
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
    //replace with a binary search, not a linear one
    //look through all the tiles
    TileInstance *tempTile;

    for(int i = 0; i < GetChildCount(); i++)
    {
         tempTile = static_cast<TileInstance*>(GetChildByIndex(i));

        //and if one in said position exists
        if(tempTile->GetX() == x && tempTile->GetY() == y)
        {
            //modify its ID
            tempTile->SetTileID(ID);
            return;
        }
    }

    //if the loop finishes, no matching tile was found
    //so we add a new one
    tempTile = new TileInstance;
    tempTile->SetX(x);
    tempTile->SetY(y);
    tempTile->SetTileID(ID);

    AddChild(tempTile);
}

int Layer::GetTileType(int x, int y)
{
    TileInstance *tempTile;

    //look through all the tiles
    for(int i = 0; i < GetChildCount(); i++)
    {
         tempTile = static_cast<TileInstance*>(GetChildByIndex(i));

        //and if one in said position exists
        if(tempTile->GetX() == x && tempTile->GetY() == y)
        {
            //return its type
            return tempTile->GetID();
        }
    }

    //if no tile with that position was found, return 0
    return 0;
}

TileInstance *Layer::GetTileAtIndex(int index)
{
    if(index < 0 || index >= GetChildCount())
        return NULL;

    return static_cast<TileInstance*>(GetChildByIndex(index));
}
