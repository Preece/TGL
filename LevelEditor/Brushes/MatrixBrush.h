#ifndef MATRIXBRUSH_H
#define MATRIXBRUSH_H

#include <QRect>

#include "SmartBrush.h"

class MatrixBrush : public SmartBrush
{
public:
    MatrixBrush();

    void Paint(int x, int y, ResourceManager *resources, bool preview);
    void Rect(int x, int y, int w, int h, ResourceManager *resources, bool preview);

    QString GetType() { return "matrix"; }

    void Press(int x, int y, ResourceManager *resources);
    void Move(int x, int y, ResourceManager *resources, bool leftButtonDown);
    void Release(int x, int y, ResourceManager *resources);

private:
    QRect currentRect;
};

#endif // MATRIXBRUSH_H
