#include "EraserBrush.h"

EraserBrush::EraserBrush()
{
}

void EraserBrush::Paint(int x, int y, TileController *tiles, bool preview)
{
    int radius = size;

    tiles->ClearEraserPreview();

    //y dimension
    for(signed int i = -radius; i <= radius; i++)
    {
        //x dimension
        for(signed int j = -radius; j <= radius; j++)
        {
            if((i*i) + (j*j) < radius * radius)
            {
                tiles->DrawEraserPreview(j + x, i + y);

                if(!preview)
                    tiles->ModifyTile(j + x, i + y, TileCoord(-1, -1));
            }
        }
    }
}

void EraserBrush::Move(int x, int y, TileController *tiles, bool leftButtonDown)
{
    tiles->ClearPreview();
    Paint(x, y, tiles, !leftButtonDown);

    //this spot is now the last spot
    lastPaintSpot.setX(x);
    lastPaintSpot.setY(y);

}
