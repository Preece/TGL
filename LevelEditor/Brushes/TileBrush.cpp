#include "TileBrush.h"

TileBrush::TileBrush()
{
}

void TileBrush::Paint(int x, int y, LayerGroup *layer, bool preview)
{
    //do nothing
}

void TileBrush::Line(int x1, int y1, int x2, int y2, LayerGroup *layer)
{
    if(x1 == x2 && y1 == y2)
        return;

    // Bresenham's line algorithm
    const bool steep = (qAbs(y2 - y1) > qAbs(x2 - x1));

    if(steep)
    {
        qSwap(x1, y1);
        qSwap(x2, y2);
    }

    if(x1 > x2)
    {
        qSwap(x1, x2);
        qSwap(y1, y2);
    }

    const float dx = x2 - x1;
    const float dy = qAbs(y2 - y1);

    float error = dx / 2.0f;
    const int ystep = (y1 < y2) ? 1 : -1;
    int y = y1;

    const int maxX = x2;

    for(int x = x1; x < maxX; x++)
    {
        if(steep)
        {
            Paint(y, x, layer);
        }
        else
        {
            Paint(x, y, layer);
        }

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
