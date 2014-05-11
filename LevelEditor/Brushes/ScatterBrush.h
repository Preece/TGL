#ifndef SCATTERBRUSH_H
#define SCATTERBRUSH_H

#include "ComplexBrush.h"

class ScatterBrush : public ComplexBrush
{
public:
    void Paint(int x, int y, ResourceController *resources, bool preview);

    ScatterBrush();
    virtual ~ScatterBrush();

    void SetFill(bool toFill) { fill = toFill; }
    void Fill(int tileX, int tileY, TileCoord newOrigin, TileCoord oldOrigin, ResourceController *resources);

    QString GetType() { return "scatter"; }
    QCursor GetCursor();

private:

    static bool fill;

};

#endif // SCATTERBRUSH_H
