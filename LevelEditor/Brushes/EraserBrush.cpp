#include "EraserBrush.h"

EraserBrush::EraserBrush()
{
    size = 1;
}

void EraserBrush::Paint(int x, int y, LayerGroup *layer)
{
    //if there is not a tile at this position
    if(layer->GetTileType(x, y) == 0)
        return;

    int radius = size;

    //y dimension
    for(signed int i = -radius; i <= radius; i++)
    {
        //x dimension
        for(signed int j = -radius; j <= radius; j++)
        {
            if((i*i) + (j*j) < radius * radius)
                layer->ModifyTile(x, y, 0);
        }
    }

}
