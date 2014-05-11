#include "TileLayer.h"

TileLayer::TileLayer()
{
    AddProperty("Name", "New Layer");
    AddProperty("Visible", true);
    AddProperty("Parallax", QPointF(1.0, 1.0));
    AddProperty("Opacity", 100);
    AddProperty("Layer Size", QPoint(0, 0));
    AddProperty("Dynamic Sizing", true);
}

TileLayer::~TileLayer()
{
}

void TileLayer::ToggleVisibility()
{
    if(GetProperty("Visible").toBool())
        SetProperty("Visible", false);
    else
        SetProperty("Visible", true);
}

bool TileLayer::ResizeToIncludePoint(int x, int y)
{
    if(GetProperty("Dynamic Sizing").toBool())
    {
        if(x > GetProperty("Layer Size").toPoint().x())
            GetProperty("Layer Size").toPoint().setX(x);

        if(y > GetProperty("Layer Size").toPoint().y())
            GetProperty("Layer Size").toPoint().setY(y);

        return true;
    }

    if(x > GetProperty("Layer Size").toPoint().x() || y > GetProperty("Layer Size").toPoint().y())
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
