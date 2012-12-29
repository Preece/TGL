#include "PencilBrush.h"

PencilBrush::PencilBrush()
{
    selectedTileID = 0;
}

void PencilBrush::Paint(int x, int y, LayerGroup *layer, bool preview)
{
    //if no tile is selected, bail
    if(selectedTileID == 0)
        return;

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
                if(overwrite || layer->GetTileType(j + x, i + y) == 0)
                {
                    if(preview)
                        layer->PreviewModifyTile(j + x, i + y, selectedTileID);
                    else
                        layer->ModifyTile(j + x, i + y, selectedTileID);
                }
            }
        }
    }
}
