#include "FillBrush.h"

FillBrush::FillBrush()
{
}

/*void LayerManager::FloodFill(int tileX, int tileY, int newTileID, int oldTileID)
{
    //this is a recursive function. It calls itself in tiles to the north, east, south and west.
    //it will return if the tile is different from the one being replaced, or off the edge of the grid

    if(!resourceManager || !currentTile || !currentLayer)
        return;

    if(newTileID == oldTileID)
        return;

    if(resourceManager->GetLevelProperties()->IsPropertiesSet())
    {
        //if the position is beyond the bounds of the scene, ignore it
        //EVENTUALLY THE PARALLAX WILL NEED TO BE CONSIDERED
        if(tileX >= resourceManager->GetLevelProperties()->GetMapWidth() ||
           tileY >= resourceManager->GetLevelProperties()->GetMapHeight() ||
           tileX < 0 || tileY < 0)
            return;

        //modify the correct tiles tileID to the one of the selection
        Layer *currentModelLayer = currentLayer->GetLayer();

        if(currentModelLayer)
        {
            //if the current tile is of the type to be replaced
            if(currentModelLayer->GetTileType(tileX, tileY) == oldTileID)
            {
                //replace this tile with the new type
                ModifyTile(tileX, tileY, false);

                //call this function on the surrounding tiles
                FloodFill(tileX - 1, tileY, newTileID, oldTileID);
                FloodFill(tileX + 1, tileY, newTileID, oldTileID);
                FloodFill(tileX, tileY - 1, newTileID, oldTileID);
                FloodFill(tileX, tileY + 1, newTileID, oldTileID);
            }
        }
    }
}*/
