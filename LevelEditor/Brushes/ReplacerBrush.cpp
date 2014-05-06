#include "ReplacerBrush.h"

ReplacerBrush::ReplacerBrush()
{
    AddList(2);
}

void ReplacerBrush::Paint(int x, int y, ResourceManager *resources, bool preview)
{
    //erase the previous preview, if we are in preview mode. Get ready for the next
    resources->ClearPreview();

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
                if(ListContainsTile(1, resources->GetTileOrigin(j + x, i + y)))
                {
                    //draw a tile from the clean list
                    if(preview)
                        resources->PreviewModifyTile(j + x, i + y, GetRandomTile(0));
                    else
                        resources->ModifyTile(j + x, i + y, GetRandomTile(0));
                }
            }
        }
    }
}

void ReplacerBrush::PushNewList(TileList tiles)
{
    if(tiles.empty())
        return;

    //make the current clean list become the current dirty list
    AddTiles(1, GetTiles(0), true);
    //and the new tiles become the clean tiles
    AddTiles(0, tiles, true);
}
