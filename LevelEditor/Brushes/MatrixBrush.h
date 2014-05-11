#ifndef MATRIXBRUSH_H
#define MATRIXBRUSH_H

#include <QRect>

#include "SmartBrush.h"

class MatrixBrush : public SmartBrush
{
public:
    MatrixBrush();

    void Paint(int, int, ResourceController *, bool);
    void Rect(int x, int y, int w, int h, ResourceController *resources, bool preview);

    QString GetType() { return "matrix"; }

    void Press(int x, int y, ResourceController *resources);
    void Move(int x, int y, ResourceController *resources, bool leftButtonDown);
    void Release(int, int, ResourceController *resources);

private:
    QRect currentRect;
};

#endif // MATRIXBRUSH_H
