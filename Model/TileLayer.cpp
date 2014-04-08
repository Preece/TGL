#include "TileLayer.h"

TileLayer::TileLayer()
{
    iter = tiles.begin();

    opacity = 100;
    verticalParallax = 1.0;
    horizontalParallax = 1.0;
}

bool TileLayer::Export(Exporter *exporter)
{
    exporter->WriteDouble(verticalParallax);
    exporter->WriteDouble(horizontalParallax);
    exporter->WriteString(name);
    exporter->WriteInt(opacity);

    return true;
}

bool TileLayer::Import(Exporter *exporter)
{
    exporter->ReadDouble(verticalParallax);
    exporter->ReadDouble(horizontalParallax);
    exporter->ReadString(name);
    exporter->ReadInt(opacity);

    return true;
}

TileCoord TileLayer::GetTileOrigin(int x, int y)
{
    Tile *tempTile;

    //if the value is 0, the tile doesnt exist
    if(!tiles.value(TileCoord(x, y)))
    {
        //so return nothing
        return TileCoord(-1, -1);
    }

    //get the tile at that position
    tempTile = tiles[TileCoord(x, y)];

    //return the ID of the tile
    return TileCoord(tempTile->origin.first, tempTile->origin.second);
}

Tile *TileLayer::AddTile(TileCoord newPos, TileCoord newOrigin)
{
    //create a new tile instance
    Tile *tempTile = new Tile;

    //fill out its values
    tempTile->pos = newPos;
    tempTile->origin = newOrigin;

    //add it to the map of tiles
    tiles[newPos] = tempTile;

    //return the new tile
    return tempTile;
}

void TileLayer::RemoveTile(TileCoord pos)
{
    //remove the specified tile
    tiles.remove(pos);
}

void TileLayer::ModifyTile(int x, int y, TileCoord newOrigin)
{
    //if the tile they are trying to modify exists
    if(tiles[TileCoord(x, y)] != 0)
    {
        //access the pointer to it and change its tileID
        Tile *tempTile = tiles[TileCoord(x, y)];
        tempTile->origin = newOrigin;
    }
}
