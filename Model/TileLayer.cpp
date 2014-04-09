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

Tile *TileLayer::AddTile(int x, int y, TileCoord newOrigin)
{
    if(tiles.value(TileCoord(x, y)))
        return NULL;

    //create a new tile instance
    Tile *tempTile = new Tile;

    //fill out its values
    tempTile->pos.first = x;
    tempTile->pos.second = y;
    tempTile->origin = newOrigin;

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

void TileLayer::ModifyTile(int x, int y, TileCoord newOrigin)
{
    //if the tile they are trying to modify exists
    if(tiles.value(TileCoord(x, y)))
    {
        //access the pointer to it and change its tileID
        Tile *tempTile = tiles[TileCoord(x, y)];
        tempTile->origin = newOrigin;
    }
}

Tile *TileLayer::GetTileByIndex(int layerID, int index)
{
    QList<Tile*> tileList = tiles.values();

    if(index >= 0 && index < tileList.count())
        return tileList[index];

    return NULL;
}
