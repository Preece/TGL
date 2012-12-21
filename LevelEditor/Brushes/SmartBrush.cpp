#include "SmartBrush.h"

void SmartBrush::Paint(int x, int y, LayerGroup *layer, bool preview)
{
    //erase the previous preview, if we are in preview mode. Get ready for the next
    if(preview)
        layer->ClearPreview();

    //paint the middle tiles. These get painted over everything
    int radius = size;

    //y dimension
    for(signed int i = -radius + 1; i < radius; i++)
    {
        //x dimension
        for(signed int j = -radius + 1; j < radius; j++)
        {
            if(overwrite || layer->GetTileType(j + x, i + y) == 0)
            {
                if(preview)
                    layer->PreviewModifyTile(j + x, i + y, GetRandomTile(4));
                else
                    layer->ModifyTile(j + x, i + y, GetRandomTile(4));
            }
        }
    }

    //paint the surrounding tiles. These do NOT paint over the middle tiles
}

SmartBrush::SmartBrush()
{
    AddList(9);
}
