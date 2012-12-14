#ifndef TILEBRUSH_H
#define TILEBRUSH_H

#include <QPoint>
#include <qmath.h>

#include "../LayerGroup.h"

class TileBrush
{
private:

public:
    TileBrush();

    virtual void Paint(int x, int y, LayerGroup *layer) = 0;
    virtual void Line(int x1, int y1, int x2, int y2, LayerGroup *layer) = 0;
};

#endif // TILEBRUSH_H
