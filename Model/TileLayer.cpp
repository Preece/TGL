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

Tile *TileLayer::GetTileAtPos(int x, int y)
{
    return tiles[TileCoord(x, y)];
}

TileCoord TileLayer::GetTileOrigin(int x, int y)
{
    Tile *tempTile;

    //get the tile at that position
    tempTile = tiles[TileCoord(x, y)];

    //if the value is 0, the tile doesnt exist
    if(tempTile == 0)
    {
        //so return nothing
        return TileCoord(0, 0);
    }

    //otherwise, return the ID of the tile
    return TileCoord(tempTile->originX, tempTile->originY);
}

Tile *TileLayer::AddTile(int x, int y, int oX, int oY)
{
    //create a new tile instance
    Tile *tempTile = new Tile;

    //fill out its values
    tempTile->x = x;
    tempTile->y = y;
    tempTile->originX = oX;
    tempTile->originY = oY;

    //add it to the map of tiles
    tiles[TileCoord(x, y)] = tempTile;

    //return the new tile
    return tempTile;
}

void TileLayer::RemoveTile(int x, int y)
{
    //remove the specified tile
    tiles.remove(TileCoord(x, y));
}

void TileLayer::ModifyTile(int x, int y, int oX, int oY)
{
    //if the tile they are trying to modify exists
    if(tiles[TileCoord(x, y)] != 0)
    {
        //access the pointer to it and change its tileID
        Tile *tempTile = tiles[TileCoord(x, y)];
        tempTile->originX = oX;
        tempTile->originY = oY;
    }
}
