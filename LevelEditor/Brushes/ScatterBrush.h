#ifndef SCATTERBRUSH_H
#define SCATTERBRUSH_H

#include "ComplexBrush.h"

class ScatterBrush : public ComplexBrush
{
public:
    void Paint(int x, int y, TileLayerView *layer, bool preview);

    ScatterBrush();
    virtual ~ScatterBrush();

    void SetFill(bool toFill) { fill = toFill; }
    void Fill(int tileX, int tileY, int newTile, int oldTile, TileLayerView *newLayer);

    QString GetType() { return "scatter"; }
private:

    static bool fill;

};

#endif // SCATTERBRUSH_H
