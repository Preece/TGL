#include "ScatterBrush.h"

bool ScatterBrush::fill = false;

ScatterBrush::ScatterBrush()
{
    AddList();
}

ScatterBrush::~ScatterBrush()
{
}

QCursor ScatterBrush::GetCursor()
{
    if(ScatterBrush::fill)
        return QCursor(QPixmap(":/Icons/scatterfill.png"), 3, 13);
    else
        return QCursor(QPixmap(":/Icons/pencil.png"), 1, 2);
}

void ScatterBrush::Paint(int x, int y, TileController *tiles, bool preview)
{
    //erase the previous preview, if we are in preview mode. Get ready for the next
    tiles->ClearPreview();

    if(fill && preview)
        return;

    if(fill && !preview)
    {
        TileCoord old = tiles->GetTileOrigin(x, y);

        Fill(x, y, GetRandomTile(0), old, tiles);

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
                if(overwrite || tiles->GetTileOrigin(j + x, i + y) == TileCoord(-1, -1))
                {
                    if(preview)
                        tiles->PreviewModifyTile(j + x, i + y, GetRandomTile(0));
                    else
                        tiles->ModifyTile(j + x, i + y, GetRandomTile(0));
                }
            }
        }
    }
}

void ScatterBrush::Fill(int tileX, int tileY, TileCoord newOrigin, TileCoord oldOrigin, TileController *tiles)
{
    //this is a recursive function. It calls itself in tiles to the north, east, south and west.
    //it will return if the tile is different from the one being replaced, or off the edge of the grid

    if(newOrigin == TileCoord(-1, -1) || newOrigin == oldOrigin)
        return;

    //if the position is beyond the bounds of the scene, ignore it
    if(tileX >= tiles->GetCurrentLayerWidth() ||
       tileY >= tiles->GetCurrentLayerHeight() ||
       tileX < 0 || tileY < 0)
           return;

    //if the current tile is of the type to be replaced
    if(tiles->GetTileOrigin(tileX, tileY) == oldOrigin)
    {
        //replace this tile with the new type
        tiles->ModifyTile(tileX, tileY, newOrigin);

        //call this function on the surrounding tiles
        Fill(tileX - 1, tileY, GetRandomTile(0), oldOrigin, tiles);
        Fill(tileX + 1, tileY, GetRandomTile(0), oldOrigin, tiles);
        Fill(tileX, tileY - 1, GetRandomTile(0), oldOrigin, tiles);
        Fill(tileX, tileY + 1, GetRandomTile(0), oldOrigin, tiles);
    }
}
