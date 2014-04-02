#ifndef STAMPBRUSH_H
#define STAMPBRUSH_H

#include <QList>

#include "TileBrush.h"

struct TilePos
{
    int x, y;
    int type;
};

class StampBrush : public TileBrush
{
public:
    StampBrush();

    void Move(int x, int y, TileLayerView *layer, bool leftButtonDown);

    void Paint(int x, int y, TileLayerView *layer, bool preview);
    QString GetType() { return "stamp"; }

    void CreateGrid(QList<QGraphicsItem*> items);

private:
    QList<Tile*> tiles;
};

#endif // STAMPBRUSH_H
