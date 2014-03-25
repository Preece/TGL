#include "PencilBrush.h"

PencilBrush::PencilBrush()
{
    selectedTileOrigin = TileCoord(-1, -1);
    lineMode = false;
}

void PencilBrush::Paint(int x, int y, TileLayerView *layer, bool preview)
{
    //if no tile is selected, bail
    if(selectedTileOrigin == TileCoord(-1, -1))
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
                if(layer->GetTileOrigin(j + x, i + y) != selectedTileOrigin)
                    if(overwrite || layer->GetTileOrigin(j + x, i + y) == TileCoord(-1, -1))
                    {
                        if(preview)
                            layer->PreviewModifyTile(j + x, i + y, selectedTileOrigin);
                        else
                            layer->ModifyTile(j + x, i + y, selectedTileOrigin);
                    }
            }
        }
    }
}
