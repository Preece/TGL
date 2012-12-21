#ifndef SMARTBRUSH_H
#define SMARTBRUSH_H

#include "ComplexBrush.h"

class SmartBrush : public ComplexBrush
{
public:

    void Paint(int x, int y, LayerGroup *layer, bool preview);

    SmartBrush();
};

#endif // SMARTBRUSH_H
