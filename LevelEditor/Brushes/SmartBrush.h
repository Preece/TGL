#ifndef SMARTBRUSH_H
#define SMARTBRUSH_H

#include "ComplexBrush.h"

class SmartBrush : public ComplexBrush
{
public:

    void Paint(int x, int y, LayerGroup *layer, bool preview);

    void ContextPaintTile(int x, int y, LayerGroup *layer, bool preview);

    SmartBrush();

    QString GetType() { return "smart"; }
};

#endif // SMARTBRUSH_H
