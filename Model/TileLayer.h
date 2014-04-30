#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItemGroup>
#include <QPoint>
#include <QHash>

#include "ItemNode.h"

class TileLayer : public ItemNode
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "layer"; }

    TileLayer();
    ~TileLayer();

    void DestroyTiles();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    void SetVerticalParallax(double newVP) { verticalParallax = newVP; }
    double GetVerticalParallax() { return verticalParallax; }
    void SetHorizontalParallax(double newHP) { horizontalParallax = newHP; }
    double GetHorizontalParallax() { return horizontalParallax; }

    void SetOpacity(int newOpacity) { opacity = newOpacity; if(opacity > 100) opacity = 100; }
    int GetOpacity() { return opacity; }

    int GetTileCount() { return tiles.count(); }
    TileCoord GetTileOrigin(int x, int y);

    Tile *AddTile(int x, int y, TileCoord newOrigin);
    void RemoveTile(int x, int y);
    void ModifyTile(int x, int y, TileCoord newOrigin);

    Tile *GetTileByIndex(int layerID, int index);

private:
    double verticalParallax, horizontalParallax;
    QString name;

    int opacity;

    QHash<TileCoord, Tile*> tiles;
};

#endif // LAYER_H
