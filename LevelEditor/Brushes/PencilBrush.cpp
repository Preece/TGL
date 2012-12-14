#include "PencilBrush.h"

PencilBrush::PencilBrush()
{
    size = 1;
    overwrite = true;
    selectedTileID = 0;
}

void PencilBrush::Paint(int x, int y, LayerGroup *layer)
{
    if(selectedTileID == 0)
        return;

    if(overwrite || layer->GetTileType(x, y) == 0)
    {
        int radius = size;

        //y dimension
        for(signed int i = -radius; i <= radius; i++)
        {
            //x dimension
            for(signed int j = -radius; j <= radius; j++)
            {
                if((i*i) + (j*j) < radius * radius)
                    layer->ModifyTile(j + x, i + y, selectedTileID);
            }
        }
    }
}
