#include "TileBrush.h"

int TileBrush::size = 1;
int TileBrush::selectedTileID = 0;

TileBrush::TileBrush()
{
    overwrite = true;
}

void TileBrush::Press(int x, int y, LayerGroup *layer)
{
    //they have started painting, so nix the preview
    layer->ClearPreview();

    if(x != lastPaintSpot.x() || y != lastPaintSpot.y())
        Paint(x, y, layer);

    lastPaintSpot.setX(x);
    lastPaintSpot.setY(y);
}

void TileBrush::Move(int x, int y, LayerGroup *layer, bool leftButtonDown)
{
    if(leftButtonDown)
    {
        //paint if the position is different from before
        if(x != lastPaintSpot.x() || y != lastPaintSpot.y())
        {
            Line(lastPaintSpot.x(), lastPaintSpot.y(), x, y, layer);

            //this spot is not the last spot
            lastPaintSpot.setX(x);
            lastPaintSpot.setY(y);
        }
    }
}

void TileBrush::Release(int x, int y, LayerGroup *layer)
{
}

void TileBrush::Paint(int x, int y, LayerGroup *layer, bool preview)
{
    //do nothing
}

void TileBrush::Line(int x1, int y1, int x2, int y2, LayerGroup *layer, bool preview)
{
    //if the tiles are at the same spot
    if(x1 == x2 && y1 == y2)
        Paint(x1, y1, layer, preview);

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

    for(int x = x1; x <= maxX; x++)
    {
        if(steep)
        {
            Paint(y, x, layer, preview);
        }
        else
        {
            Paint(x, y, layer, preview);
        }

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
