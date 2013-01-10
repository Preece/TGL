#ifndef MATRIXBRUSH_H
#define MATRIXBRUSH_H

#include <QRect>

#include "ComplexBrush.h"

class MatrixBrush : public ComplexBrush
{
public:
    MatrixBrush();

    void Paint(int x, int y, LayerGroup *layer, bool preview);
    void Rect(int x, int y, int w, int h, LayerGroup *layer, bool preview);

    QString GetType() { return "matrix"; }

    void Press(int x, int y, LayerGroup *layer);
    void Move(int x, int y, LayerGroup *layer, bool leftButtonDown);
    void Release(int x, int y, LayerGroup *layer);

    void ContextPaintTile(int x, int y, LayerGroup *layer, bool preview);

private:
    QRect currentRect;
};

#endif // MATRIXBRUSH_H
