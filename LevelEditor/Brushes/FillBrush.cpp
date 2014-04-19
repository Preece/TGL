#include "FillBrush.h"

FillBrush::FillBrush()
{
    selectedTileOrigin = TileCoord(-1, -1);
}

FillBrush::~FillBrush()
{

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

    TileCoord old = layer->GetTileOrigin(x, y);

    Fill(x, y, selectedTileOrigin, old, layer);
}

void FillBrush::Fill(int tileX, int tileY, TileCoord newOrigin, TileCoord oldOrigin, TileLayerView *newLayer)
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

    // 2. Set Q to the empty queue.
    QStack<TileCoord> seedQueue;

    // 3. Add node to the end of Q.
    seedQueue.push(TileCoord(tileX, tileY));

    int layerWidth = newLayer->GetLayerWidth();
    int layerHeight = newLayer->GetLayerHeight();

    QHash<TileCoord,bool> examinedTiles;

    // 4. While Q is not empty:
    while(!seedQueue.isEmpty())
    {
        // 5.     Set n equal to the last element of Q.
        TileCoord tempCoord = seedQueue.pop();

        //if the position is beyond the bounds of the scene, ignore it
        if(tempCoord.first >= layerWidth ||
           tempCoord.second >= layerHeight ||
           tempCoord.first < 0 || tempCoord.second < 0)
               continue;

        //if this tile has already been examined, move on. No need to check again
        if(examinedTiles.contains(tempCoord))
            continue;

        //indicate that this spot has been examined
        examinedTiles[tempCoord] = true;

        //if this tile is of the type to be replaced
        if(newLayer->GetTileOrigin(tempCoord.first, tempCoord.second) == oldOrigin)
        {
            //replace this tile with the new type
            newLayer->ModifyTileItem(tempCoord.first, tempCoord.second, newOrigin);

            //put the four surrounding tiles on the stack
            seedQueue.push_back(TileCoord(tempCoord.first - 1, tempCoord.second));
            seedQueue.push_back(TileCoord(tempCoord.first + 1, tempCoord.second));
            seedQueue.push_back(TileCoord(tempCoord.first, tempCoord.second - 1));
            seedQueue.push_back(TileCoord(tempCoord.first, tempCoord.second + 1));
        }
    }

    //1. Set Q to the empty queue.
    //QList<TileCoord> seedQueue;

    //3. Add node to Q.
    //seedQueue.push_back(TileCoord(tileX, tileY));

    //4. For each element N of Q:
    //while(!seedQueue.isEmpty())
    //{
        //if the position is beyond the bounds of the scene, ignore it
        //if(tempCoord.first >= newLayer->GetLayerWidth() ||
            //tempCoord.second >= newLayer->GetLayerHeight() ||
            //tempCoord.first < 0 || tempCoord.second < 0)
                //continue;

         //5.     If the color of N is equal to target-color:
        //if(newLayer->GetTileOrigin(tempCoord.first, tempCoord.second) == oldOrigin)
        //{

    //6.         Set w and e equal to N.
    //7.         Move w to the west until the color of the node to the west of w no longer matches target-color.
    //8.         Move e to the east until the color of the node to the east of e no longer matches target-color.
    //9.         For each node n between w and e:
   //10.             Set the color of n to replacement-color.
   //11.             If the color of the node to the north of n is target-color, add that node to Q.
   //12.             If the color of the node to the south of n is target-color, add that node to Q.
        //}
   //}
}
