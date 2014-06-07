#include "TileLayer.h"

TileLayer::TileLayer()
{
    AddProperty("Name", "New Layer");
    AddProperty("Visible", true);
    AddProperty("Parallax", QPointF(1.0, 1.0));
    AddProperty("Opacity", 100);
    AddProperty("Layer Size", QPoint(0, 0));
    AddProperty("Dynamic Sizing", true);
    AddProperty("Stack Order", 0);
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
    if(x < 0 || y < 0)
        return false;

    if(GetProperty("Dynamic Sizing").toBool())
    {
        QPoint newSize(GetProperty("Layer Size").toPoint());


        if(x > newSize.x())
            newSize.setX(x);

        if(y > newSize.y())
            newSize.setY(y);

        SetProperty("Layer Size", newSize);

        return true;
    }

    if(x > GetProperty("Layer Size").toPoint().x() || y > GetProperty("Layer Size").toPoint().y())
        return false;

    return true;
}

bool TileLayer::PointIsWithinLayer(int x, int y)
{
    QPoint layerSize(GetProperty("Layer Size").toPoint());

    if(layerSize.x() < x || layerSize.y() < y)
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
