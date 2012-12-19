#include "ScatterBrush.h"

void ScatterBrush::Paint(int x, int y, LayerGroup *layer, bool preview)
{
    //erase the previous preview, if we are in preview mode. Get ready for the next
    if(preview)
        layer->ClearPreview();

    int radius = size;

    //y dimension
    for(signed int i = -radius; i <= radius; i++)
    {
        //x dimension
        for(signed int j = -radius; j <= radius; j++)
        {
            if((i*i) + (j*j) < (radius * radius))
            {
                if(overwrite || layer->GetTileType(j + x, i + y) == 0)
                {
                    if(preview)
                        layer->PreviewModifyTile(j + x, i + y, GetRandomTile());
                    else
                        layer->ModifyTile(j + x, i + y, GetRandomTile());
                }
            }
        }
    }
}

ScatterBrush::ScatterBrush()
{
}

int ScatterBrush::GetRandomTile()
{
    if(tiles.count() == 0)
        return 0;

    int rand = qrand() % (tiles.count());

    return tiles[rand];
}
