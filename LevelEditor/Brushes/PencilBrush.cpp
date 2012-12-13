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

    //must factor in brushes larger than 1 later
    if(overwrite)
    {
        layer->ModifyTile(x, y, selectedTileID);
    }
    else
    {
        if(layer->GetTileType(x, y) == 0)
            layer->ModifyTile(x, y, selectedTileID);
    }
}
