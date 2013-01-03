#ifndef REPLACERBRUSH_H
#define REPLACERBRUSH_H

#include "ComplexBrush.h"

class ReplacerBrush : public ComplexBrush
{
public:
    ReplacerBrush();

    void Paint(int x, int y, LayerGroup *layer, bool preview);
};

#endif // REPLACERBRUSH_H
