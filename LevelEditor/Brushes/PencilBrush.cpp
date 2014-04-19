#include "PencilBrush.h"

PencilBrush::PencilBrush()
{
    selectedTileOrigin = TileCoord(-1, -1);
    lineMode = false;
}

PencilBrush::~PencilBrush()
{

}

void PencilBrush::Paint(int x, int y, TileLayerView *layer, bool preview)
{
    //if no tile is selected, bail
    if(selectedTileOrigin == TileCoord(-1, -1))
        return;

    //erase the previous preview, if we are in preview mode. Get ready for the next.
    //test removing this. might be wasting time doing nothing here
    //layer->ClearPreview();

    int radius = size;
    int radiusSquared = radius * radius;

    //y dimension
    for(signed int i = -radius; i <= radius; i++)
    {
        int iSquared = i * i;
        //x dimension
        for(signed int j = -radius; j <= radius; j++)
        {
            //constrain to within the radius of the drawing circle
            if((iSquared + (j*j)) < radiusSquared)
            {
                TileCoord currOrigin = layer->GetTileOrigin(j + x, i + y);

                //and make sure the draw operation would not be painting the same tile
                if(currOrigin != selectedTileOrigin)
                {
                    //if they have either selected to overwrite other tiles,
                    //or the tile they are painting on is empty
                    if(overwrite || currOrigin == TileCoord(-1, -1))
                    {
                        //paint either a preview or an actual tile
                        if(preview)
                            layer->PreviewModifyTile(j + x, i + y, selectedTileOrigin);
                        else
                            layer->ModifyTileItem(j + x, i + y, selectedTileOrigin);
                    }
                }
            }
        }
    }
}
