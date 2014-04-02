#ifndef STAMPBRUSH_H
#define STAMPBRUSH_H

#include <QList>

#include "TileBrush.h"

class StampBrush : public TileBrush
{
public:
    StampBrush();

    void Move(int x, int y, TileLayerView *layer, bool leftButtonDown);

    void Paint(int x, int y, TileLayerView *layer, bool preview);
    QString GetType() { return "stamp"; }

    void CreateGrid(QList<TileOrigin> items);

private:
    QList<TileItem*> tiles;
    
    int avgX, avgY;
};

#endif // STAMPBRUSH_H
