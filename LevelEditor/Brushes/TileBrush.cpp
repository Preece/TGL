#include "TileBrush.h"

int TileBrush::size = 1;
TileCoord TileBrush::selectedTileOrigin = TileCoord(-1, -1);

TileBrush::TileBrush()
{
    overwrite = true;
}

TileBrush::~TileBrush()
{

}

void TileBrush::Press(int x, int y, ResourceManager *resources)
{
    //they have started painting, so nix the preview
    resources->ClearPreview();

    if(x != lastPaintSpot.x() || y != lastPaintSpot.y())
        Paint(x, y, resources);

    lastPaintSpot.setX(x);
    lastPaintSpot.setY(y);
}

void TileBrush::Move(int x, int y, ResourceManager *resources, bool leftButtonDown)
{
    if(leftButtonDown)
    {
        //paint if the position is different from before
        if(x != lastPaintSpot.x() || y != lastPaintSpot.y())
        {
            Line(lastPaintSpot.x(), lastPaintSpot.y(), x, y, resources);

            //this spot is now the last spot
            lastPaintSpot.setX(x);
            lastPaintSpot.setY(y);
        }
    }
    else
    {
        //paint if the position is different from before
        if(x != lastPreviewSpot.x() || y != lastPreviewSpot.y())
        {
            resources->ClearPreview();
            Paint(x, y, resources, true);

            //this spot is now the last spot
            lastPreviewSpot.setX(x);
            lastPreviewSpot.setY(y);
        }
    }
}

void TileBrush::Release(int, int, ResourceManager *)
{
}

void TileBrush::Paint(int, int, ResourceManager *, bool)
{
    //do nothing
}

void TileBrush::Line(int x1, int y1, int x2, int y2, ResourceManager *resources, bool preview)
{
    //if the tiles are at the same spot
    if(x1 == x2 && y1 == y2)
        Paint(x1, y1, resources, preview);

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
            Paint(y, x, resources, preview);
        }
        else
        {
            Paint(x, y, resources, preview);
        }

        error -= dy;
        if(error < 0)
        {
            y += ystep;
            error += dx;
        }
    }
}
