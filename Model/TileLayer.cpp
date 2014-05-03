#include "TileLayer.h"

TileLayer::TileLayer()
{
    opacity = 100;
    verticalParallax = 1.0;
    horizontalParallax = 1.0;
}

TileLayer::~TileLayer()
{
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
    if(!tiles.contains(TileCoord(x, y)))
        return TileCoord(-1, -1);

    //return the origin of the tile
    return tiles[TileCoord(x, y)].origin;
}

void TileLayer::ModifyTile(int x, int y, TileCoord newOrigin)
{
    //if the tile they are trying to modify exists
    if(tiles.contains(TileCoord(x, y)))
    {
        if(newOrigin == TileCoord(-1, -1))
            tiles.remove(TileCoord(x, y));
        else
            tiles[TileCoord(x, y)].origin = newOrigin;
    }
    else
    {
        Tile tempTile;
        tempTile.pos.first = x;
        tempTile.pos.second = y;
        tempTile.origin = newOrigin;
        tiles[tempTile.pos] = tempTile;
    }
}
