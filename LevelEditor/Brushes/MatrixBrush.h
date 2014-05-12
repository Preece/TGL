#ifndef MATRIXBRUSH_H
#define MATRIXBRUSH_H

#include <QRect>

#include "SmartBrush.h"

class MatrixBrush : public SmartBrush
{
public:
    MatrixBrush();

    void Paint(int, int, TileController *, bool);
    void Rect(int x, int y, int w, int h, TileController *tiles, bool preview);

    QString GetType() { return "matrix"; }

    void Press(int x, int y, TileController *tiles);
    void Move(int x, int y, TileController *tiles, bool leftButtonDown);
    void Release(int, int, TileController *tiles);

private:
    QRect currentRect;
};

#endif // MATRIXBRUSH_H
