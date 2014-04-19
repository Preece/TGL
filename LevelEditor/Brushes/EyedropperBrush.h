#ifndef EYEDROPPERBRUSH_H
#define EYEDROPPERBRUSH_H

#include "TileBrush.h"

class EyedropperBrush : public TileBrush
{
public:
    EyedropperBrush();

    virtual void Press(int x, int y, TileLayerView *layer);
    virtual void Move(int x, int y, TileLayerView *layer, bool leftButtonDown);
    virtual void Release(int x, int y, TileLayerView *layer);

    virtual void Paint(int x, int y, TileLayerView *layer, bool preview = false);

    QString GetType() { return "eyedropper"; }
};

#endif // EYEDROPPERBRUSH_H
