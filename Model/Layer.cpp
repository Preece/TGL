#include "Layer.h"

Layer::Layer()
{
    iter = tiles.begin();
}

bool Layer::Export(Exporter *exporter)
{
    exporter->WriteDouble(verticalParallax);
    exporter->WriteDouble(horizontalParallax);
    exporter->WriteString(name);
    exporter->WriteInt(opacity);

    return true;
}

bool Layer::Import(Exporter *exporter)
{
    exporter->ReadDouble(verticalParallax);
    exporter->ReadDouble(horizontalParallax);
    exporter->ReadString(name);
    exporter->ReadInt(opacity);

    return true;
}

TileInstance *Layer::GetTileAtIndex(int index)
{
    if(index < 0 || index >= GetTileCount())
        return NULL;

    //temporarily commented out as I try to make a QMap hold the tiles
    //return static_cast<TileInstance*>(GetChildByIndex(index));

}

TileInstance *Layer::GetTileAtPos(int x, int y)
{
    return tiles[TileCoord(x, y)];
}

int Layer::GetTileType(int x, int y)
{
    TileInstance *tempTile;

    /*for(int i = 0; i < GetChildCount(); i++)
    {
        tempTile = static_cast<TileInstance*>(GetChildByIndex(i));

        //if the tile exists at the specified position, change it
        if(tempTile->GetX() == x && tempTile->GetY() == y)
        {
            return tempTile->GetTileID();
        }
    }*/

    //get the tile at that position
    tempTile = tiles[TileCoord(x, y)];

    //if the value is 0, the tile doesnt exist
    if(tempTile == 0)
    {
        //so return nothing
        return 0;
    }

    //otherwise, return the ID of the tile
    return tempTile->GetTileID();
}

TileInstance *Layer::AddTile(int x, int y, int ID)
{
    //create a new tile instance
    TileInstance *tempTile = new TileInstance;

    //fill out its values
    tempTile->SetX(x);
    tempTile->SetY(y);
    tempTile->SetTileID(ID);

    //add it to the map of tiles
    tiles[TileCoord(x, y)] = tempTile;

    //AddChild(tempTile);

    //return the new tile
    return tempTile;
}

void Layer::RemoveTile(int x, int y)
{
    TileInstance *tempTile;

    /*for(int i = 0; i < GetChildCount(); i++)
    {
        tempTile = static_cast<TileInstance*>(GetChildByIndex(i));

        //if the tile exists at the specified position, change it
        if(tempTile->GetX() == x && tempTile->GetY() == y)
        {
            RemoveChild(tempTile->GetID());
            return;
        }
    }*/

    //remove the specified tile
    tiles.remove(TileCoord(x, y));
}

void Layer::ModifyTile(int x, int y, int ID)
{
    TileInstance *tempTile;

    /*for(int i = 0; i < GetChildCount(); i++)
    {
        tempTile = static_cast<TileInstance*>(GetChildByIndex(i));

        //if the tile exists at the specified position, change it
        if(tempTile->GetX() == x && tempTile->GetY() == y)
        {
            tempTile->SetTileID(ID);
            return;
        }
    }*/

    //if the tile they are trying to modify exists
    if(tiles[TileCoord(x, y)] != 0)
    {
        //access the pointer to it and change its tileID
        tempTile = tiles[TileCoord(x, y)];
        tempTile->SetTileID(ID);
    }
}
