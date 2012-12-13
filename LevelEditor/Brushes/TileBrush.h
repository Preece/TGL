#ifndef TILEBRUSH_H
#define TILEBRUSH_H

#include <QPoint>

#include "../LayerGroup.h"

class TileBrush
{
private:

public:
    TileBrush();

    virtual void Paint(int x, int y, LayerGroup *layer) = 0;
};

#endif // TILEBRUSH_H
