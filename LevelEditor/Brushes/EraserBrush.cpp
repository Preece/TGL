#include "EraserBrush.h"

EraserBrush::EraserBrush()
{
}

void EraserBrush::Paint(int x, int y, ResourceManager *resources, bool preview)
{
    int radius = size;

    resources->ClearEraserPreview();

    //y dimension
    for(signed int i = -radius; i <= radius; i++)
    {
        //x dimension
        for(signed int j = -radius; j <= radius; j++)
        {
            if((i*i) + (j*j) < radius * radius)
            {
                resources->DrawEraserPreview(j + x, i + y);

                if(!preview)
                    resources->ModifyTile(j + x, i + y, TileCoord(-1, -1));
            }
        }
    }
}
