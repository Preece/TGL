#ifndef ERASERBRUSH_H
#define ERASERBRUSH_H

#include "TileBrush.h"

class EraserBrush : public TileBrush
{
public:
    EraserBrush();

    void Paint(int x, int y, LayerGroup *layer);

private:
    int size;
};

#endif // ERASERBRUSH_H
