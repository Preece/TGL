#include "TileLayer.h"

TileLayer::TileLayer()
{
    opacity = 100;
    width = height = 0;
    verticalParallax = 1.0;
    horizontalParallax = 1.0;

    dynamicSizing = true;
}

TileLayer::~TileLayer()
{
}

bool TileLayer::ResizeToIncludePoint(int x, int y)
{
    if(dynamicSizing)
    {
        if(x > width)
            width = x;

        if(y > height)
            height = y;

        return true;
    }

    if(x > width || y > height)
        return false;

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
