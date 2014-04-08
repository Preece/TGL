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
            //constrain to within the radius of the drawing circle
            if((i*i) + (j*j) < (radius * radius))
            {
                //and make sure the draw operation would not be painting the same tile
                if(layer->GetTileOrigin(j + x, i + y) != selectedTileOrigin)
                {
                    //if they have either selected to overwrite other tiles,
                    //or the tile they are painting on is empty
                    if(overwrite || layer->GetTileOrigin(j + x, i + y) == TileCoord(-1, -1))
                    {
                        //paint either a preview or an actual tile
                        if(preview)
                            layer->PreviewModifyTile(j + x, i + y, selectedTileOrigin);
                        else
                            layer->ModifyTile(j + x, i + y, selectedTileOrigin);
                    }
                }
            }
        }
    }
}
