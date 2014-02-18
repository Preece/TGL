#include "FillBrush.h"

FillBrush::FillBrush()
{
    selectedTileID = 0;
}

void FillBrush::Move(int x, int y, TileLayerView *layer)
{
    //we don't want this to do anything for a fill brush
}

void FillBrush::Paint(int x, int y, TileLayerView *layer, bool preview)
{
    //the fill brush has no preview mode
    if(preview)
        return;

    int old = layer->GetTileType(x, y);

    Fill(x, y, selectedTileID, old, layer);
}

void FillBrush::Fill(int tileX, int tileY, int newTile, int oldTile, TileLayerView *newLayer)
{
    //this is a recursive function. It calls itself in tiles to the north, east, south and west.
    //it will return if the tile is different from the one being replaced, or off the edge of the grid

    if(!newLayer || newTile == 0 || newTile == oldTile)
        return;

    //if the position is beyond the bounds of the scene, ignore it
    if(tileX >= newLayer->GetLayerWidth() ||
       tileY >= newLayer->GetLayerHeight() ||
       tileX < 0 || tileY < 0)
           return;

    //if the current tile is of the type to be replaced
    if(newLayer->GetTileType(tileX, tileY) == oldTile)
    {
        //replace this tile with the new type
        newLayer->ModifyTile(tileX, tileY, newTile);

        //call this function on the surrounding tiles
        Fill(tileX - 1, tileY, newTile, oldTile, newLayer);
        Fill(tileX + 1, tileY, newTile, oldTile, newLayer);
        Fill(tileX, tileY - 1, newTile, oldTile, newLayer);
        Fill(tileX, tileY + 1, newTile, oldTile, newLayer);
    }
}
