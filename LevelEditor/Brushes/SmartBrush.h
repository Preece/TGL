#ifndef SMARTBRUSH_H
#define SMARTBRUSH_H

#include "ComplexBrush.h"

class SmartBrush : public ComplexBrush
{
public:
    SmartBrush();
    ~SmartBrush();

    virtual void Paint(int x, int y, TileLayerView *layer, bool preview);
    void ContextPaintTile(int x, int y, TileLayerView *layer, bool preview);
    virtual QString GetType() { return "smart"; }
};

#endif // SMARTBRUSH_H
