#ifndef SCATTERBRUSH_H
#define SCATTERBRUSH_H

#include "ComplexBrush.h"

class ScatterBrush : public ComplexBrush
{
public:
    void Paint(int x, int y, LayerGroup *layer, bool preview);

    ScatterBrush();

private:

};

#endif // SCATTERBRUSH_H
