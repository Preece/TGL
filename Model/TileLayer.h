#ifndef LAYER_H
#define LAYER_H

#include <QHash>

#include "ResourceNode.h"

class TileLayer : public ResourceNode
{
public:
    TileLayer();
    ~TileLayer();

    QString GetName() { return GetProperty("Name").toString(); }
    void SetName(QString newName) { SetProperty("Name", newName); }

    void SetVerticalParallax(double newVP) { GetProperty("Parallax").toPoint().setY(newVP); }
    double GetVerticalParallax() { return 1.0; }
    void SetHorizontalParallax(double newHP) { GetProperty("Parallax").toPoint().setX(newHP); }
    double GetHorizontalParallax() { return 1.0; }

    void SetOpacity(int newOpacity) { SetProperty("Opacity", newOpacity); }
    int GetOpacity() { return 100; }

    void SetVisibility(bool visible) { SetProperty("Visible", visible); }
    bool GetVisibility() { return GetProperty("Visible").toBool(); }
    void ToggleVisibility();

    void SetSize(int w, int h) { SetProperty("Layer Size", QPoint(w, h)); }
    int GetWidth() { return GetProperty("Layer Size").toPoint().x(); }
    int GetHeight() { return GetProperty("Layer Size").toPoint().y(); }

    void ToggleDynamicSizing(bool dyn) { SetProperty("Dynamic Sizing", dyn); }
    bool DynamicSizingEnabled() { return GetProperty("Dynamic Sizing").toBool(); }

    bool ResizeToIncludePoint(int x, int y);
    bool PointIsWithinLayer(int x, int y);

    TileCoord GetTileOrigin(int x, int y);

    void ModifyTile(int x, int y, TileCoord newOrigin);

    QHash<TileCoord, Tile> GetAllTiles() { return tiles; }

private:

    QHash<TileCoord, Tile> tiles;
};

#endif // LAYER_H
