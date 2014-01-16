#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItemGroup>
#include <QPair>
#include <QMap>

#include "Savable.h"
#include "TileInstance.h"

typedef QPair<int, int> TileCoord;

class Layer : public Savable
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "LAYR"; }

    Layer();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    void SetVerticalParallax(double newVP) { verticalParallax = newVP; }
    double GetVerticalParallax() { return verticalParallax; }
    void SetHorizontalParallax(double newHP) { horizontalParallax = newHP; }
    double GetHorizontalParallax() { return horizontalParallax; }

    void SetOpacity(int newOpacity) { opacity = newOpacity; if(opacity > 100) opacity = 100; }
    int GetOpacity() { return opacity; }

    int GetTileCount() { return tiles.count(); }
    TileInstance *GetTileAtIndex(int index);
    TileInstance *GetTileAtPos(int x, int y);
    int GetTileType(int x, int y);

    TileInstance *AddTile(int x = 0, int y = 0, int ID = 0);
    void RemoveTile(int x, int y);
    void ModifyTile(int x, int y, int ID);

    void ResetIterator() { iter = tiles.begin(); }
    TileInstance *GetTileInstance() { return iter.value(); }
    void AdvanceIterator() { iter++; }

private:
    double verticalParallax, horizontalParallax;
    QString name;

    int opacity;

    QMap<TileCoord, TileInstance*> tiles;
    QMap<TileCoord, TileInstance*>::iterator iter;
};

#endif // LAYER_H
