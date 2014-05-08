#ifndef LAYER_H
#define LAYER_H

#include <QHash>

#include "ItemNode.h"

class TileLayer : public ObjectNode
{
public:
    TileLayer();
    ~TileLayer();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    void SetVerticalParallax(double newVP) { verticalParallax = newVP; }
    double GetVerticalParallax() { return verticalParallax; }
    void SetHorizontalParallax(double newHP) { horizontalParallax = newHP; }
    double GetHorizontalParallax() { return horizontalParallax; }

    void SetOpacity(int newOpacity) { opacity = newOpacity; if(opacity > 100) opacity = 100; }
    int GetOpacity() { return opacity; }

    void SetSize(int w, int h) { width = w; height = h; }
    int GetWidth() { return width; }
    int GetHeight() { return height; }

    void ToggleDynamicSizing(bool dyn) { dynamicSizing = dyn; }
    bool DynamicSizingEnabled() { return dynamicSizing; }

    bool ResizeToIncludePoint(int x, int y);

    TileCoord GetTileOrigin(int x, int y);

    void ModifyTile(int x, int y, TileCoord newOrigin);

private:
    double verticalParallax, horizontalParallax;
    QString name;

    int opacity;
    int width, height;
    bool dynamicSizing;

    QHash<TileCoord, Tile> tiles;
};

#endif // LAYER_H
