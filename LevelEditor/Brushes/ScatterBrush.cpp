#include "ScatterBrush.h"

bool ScatterBrush::fill = false;

void ScatterBrush::Paint(int x, int y, TileLayerView *layer, bool preview)
{
    //erase the previous preview, if we are in preview mode. Get ready for the next
    layer->ClearPreview();

    if(fill && !preview)
    {
        TileCoord old = layer->GetTileOrigin(x, y);

        Fill(x, y, GetRandomTile(0), old, layer);

        return;
    }

    int radius = size;

    //y dimension
    for(signed int i = -radius; i <= radius; i++)
    {
        //x dimension
        for(signed int j = -radius; j <= radius; j++)
        {
            if((i*i) + (j*j) < (radius * radius))
            {
                if(overwrite || layer->GetTileOrigin(j + x, i + y) == TileCoord(-1, -1))
                {
                    if(preview)
                        layer->PreviewModifyTile(j + x, i + y, GetRandomTile(0));
                    else
                        layer->ModifyTile(j + x, i + y, GetRandomTile(0));
                }
            }
        }
    }
}

ScatterBrush::ScatterBrush()
{
    AddList();
}

ScatterBrush::~ScatterBrush()
{
}

void ScatterBrush::Fill(int tileX, int tileY, TileCoord newOrigin, TileCoord oldOrigin, TileLayerView *newLayer)
{
    //this is a recursive function. It calls itself in tiles to the north, east, south and west.
    //it will return if the tile is different from the one being replaced, or off the edge of the grid

    if(!newLayer || newOrigin == TileCoord(-1, -1) || newOrigin == oldOrigin)
        return;

    //if the position is beyond the bounds of the scene, ignore it
    if(tileX >= newLayer->GetLayerWidth() ||
       tileY >= newLayer->GetLayerHeight() ||
       tileX < 0 || tileY < 0)
           return;

    //if the current tile is of the type to be replaced
    if(newLayer->GetTileOrigin(tileX, tileY) == oldOrigin)
    {
        //replace this tile with the new type
        newLayer->ModifyTile(tileX, tileY, newOrigin);

        //call this function on the surrounding tiles
        Fill(tileX - 1, tileY, GetRandomTile(0), oldOrigin, newLayer);
        Fill(tileX + 1, tileY, GetRandomTile(0), oldOrigin, newLayer);
        Fill(tileX, tileY - 1, GetRandomTile(0), oldOrigin, newLayer);
        Fill(tileX, tileY + 1, GetRandomTile(0), oldOrigin, newLayer);
    }
}
