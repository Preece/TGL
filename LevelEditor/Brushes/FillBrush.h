#ifndef FILLBRUSH_H
#define FILLBRUSH_H

#include <QStack>

#include "TileBrush.h"

class FillBrush : public TileBrush
{
public:
    FillBrush();
    ~FillBrush();

    void Move(int, int, TileController *);

    void Paint(int x, int y, TileController *tiles, bool preview = false);
    void Fill(int tileX, int tileY, TileCoord newOrigin, TileCoord oldOrigin, TileController *tiles);

    QString GetType() { return "fill"; }
    QCursor GetCursor() { return QCursor(QPixmap(":/Icons/bucket.png"), 3, 13); }

};

#endif // FILLBRUSH_H
