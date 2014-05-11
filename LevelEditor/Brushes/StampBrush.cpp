#include "StampBrush.h"

StampBrush::StampBrush()
{
    avgX = 0;
    avgY = 0;
}

StampBrush::~StampBrush()
{

}

void StampBrush::Move(int x, int y, ResourceController *resources, bool)
{
    resources->ClearPreview();

    Paint(x, y, resources, true);
}

void StampBrush::Paint(int x, int y, ResourceController *resources, bool preview)
{
    //the trick is to take the position to paint
    //add the tile origin coordinates
    //remove the average of the tile origin coordinates.
    
    //the result is that you will paint the tiles in the
    //configuration in which they have been selected in the
    //tile selector, from the middlemost point
    
    for(int i = 0; i < tiles.count(); i++)
    {
        int paintSpotX = x + tiles[i].first - avgX;
        int paintSpotY = y + tiles[i].second - avgY;
        
        if(preview)
            resources->PreviewModifyTile(paintSpotX, paintSpotY, tiles[i]);
        else
            resources->ModifyTile(paintSpotX, paintSpotY, tiles[i]);
    }
}

void StampBrush::CreateGrid(QList<TileCoord> items)
{
    //remove all current items
    tiles.clear();

    avgX = 0;
    avgY = 0;

    //loop through the items and fill the list
    for(int i = 0; i < items.count(); i++)
    {
        //add it into the list of items
        tiles.append(items[i]);
            
        //add its origin points to the tally of origins
        avgX += items[i].first;
        avgY += items[i].second;
    }
    
    if(tiles.count() > 0)
    {
        //create the averages
        avgX = (int)(avgX / tiles.count());
        avgY = (int)(avgY / tiles.count());
    }
    else
    {
        avgX = 0;
        avgY = 0;
    }
}
