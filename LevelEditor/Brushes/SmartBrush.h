#ifndef SMARTBRUSH_H
#define SMARTBRUSH_H

#include "ComplexBrush.h"

class SmartBrush : public ComplexBrush
{
public:

    virtual void Paint(int x, int y, TileLayer *layer, bool preview);

    void ContextPaintTile(int x, int y, TileLayer *layer, bool preview);

    SmartBrush();

    virtual QString GetType() { return "smart"; }
};

#endif // SMARTBRUSH_H
