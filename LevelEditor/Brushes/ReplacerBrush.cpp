#include "ReplacerBrush.h"

ReplacerBrush::ReplacerBrush()
{
    AddList(2);
}

void ReplacerBrush::Paint(int x, int y, LayerGroup *layer, bool preview)
{
    //erase the previous preview, if we are in preview mode. Get ready for the next
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
                //if the tile exists in the dirty list
                if(ListContainsTile(1, layer->GetTileType(j + x, i + y)))
                {
                    //draw a tile from the clean list
                    if(preview)
                        layer->PreviewModifyTile(j + x, i + y, GetRandomTile(0));
                    else
                        layer->ModifyTile(j + x, i + y, GetRandomTile(0));
                }
            }
        }
    }
}
