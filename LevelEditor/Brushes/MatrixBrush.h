#ifndef MATRIXBRUSH_H
#define MATRIXBRUSH_H

#include <QRect>

#include "SmartBrush.h"

class MatrixBrush : public SmartBrush
{
public:
    MatrixBrush();

    void Paint(int x, int y, TileLayer *layer, bool preview);
    void Rect(int x, int y, int w, int h, TileLayer *layer, bool preview);

    QString GetType() { return "matrix"; }

    void Press(int x, int y, TileLayer *layer);
    void Move(int x, int y, TileLayer *layer, bool leftButtonDown);
    void Release(int x, int y, TileLayer *layer);

private:
    QRect currentRect;
};

#endif // MATRIXBRUSH_H
