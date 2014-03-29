#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItemGroup>
#include <QPair>
#include <QMap>

#include "ItemNode.h"

typedef QPair<int, int> TileCoord;

struct Tile
{
    int x, y;
    int originX, originY;
};

class TileLayer : public ItemNode
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "LAYR"; }

    TileLayer();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    void SetVerticalParallax(double newVP) { verticalParallax = newVP; }
    double GetVerticalParallax() { return verticalParallax; }
    void SetHorizontalParallax(double newHP) { horizontalParallax = newHP; }
    double GetHorizontalParallax() { return horizontalParallax; }

    void SetOpacity(int newOpacity) { opacity = newOpacity; if(opacity > 100) opacity = 100; }
    int GetOpacity() { return opacity; }

    int GetTileCount() { return tiles.count(); }
    Tile *GetTileAtIndex(int index);
    Tile *GetTileAtPos(int x, int y);
    TileCoord GetTileOrigin(int x, int y);

    Tile *AddTile(int x = 0, int y = 0, int oX = 0, int oY = 0);
    void RemoveTile(int x, int y);
    void ModifyTile(int x, int y, int oX, int oY);

    void ResetIterator() { iter = tiles.begin(); }
    Tile *GetTileFromIterator() { return iter.value(); }
    void AdvanceIterator() { iter++; }

private:
    double verticalParallax, horizontalParallax;
    QString name;

    int opacity;

    QMap<TileCoord, Tile*> tiles;
    QMap<TileCoord, Tile*>::iterator iter;
};

#endif // LAYER_H
