#include "EraserBrush.h"

EraserBrush::EraserBrush()
{
}

void EraserBrush::Paint(int x, int y, TileLayer *layer, bool preview)
{
    if(preview)
        return;

    int radius = size;

    //y dimension
    for(signed int i = -radius; i <= radius; i++)
    {
        //x dimension
        for(signed int j = -radius; j <= radius; j++)
        {
            if((i*i) + (j*j) < radius * radius)
            {
                if(layer->GetTileType(j + x, i + y) != 0)
                    layer->ModifyTile(j + x, i + y, 0);
            }
        }
    }

}
