#ifndef STAMPBRUSH_H
#define STAMPBRUSH_H

#include <QList>

#include "TileBrush.h"

class StampBrush : public TileBrush
{
public:
    StampBrush();
    ~StampBrush();

    void Move(int x, int y, ResourceManager *resources, bool);

    void Paint(int x, int y, ResourceManager *resources, bool preview);
    QString GetType() { return "stamp"; }

    void CreateGrid(QList<TileCoord> items);

    QCursor GetCursor() { return QCursor(QPixmap(":/Icons/stamp.png"), 8, 13); }

private:
    QList<TileCoord> tiles;
    
    int avgX, avgY;
};

#endif // STAMPBRUSH_H
