#include "StampBrush.h"

StampBrush::StampBrush()
{
    avgX = 0;
    avgY = 0;
}

StampBrush::~StampBrush()
{

}

void StampBrush::Move(int x, int y, TileController *tiles, bool)
{
    tiles->ClearPreview();

    Paint(x, y, tiles, true);
}

void StampBrush::Paint(int x, int y, TileController *tiles, bool preview)
{
    //the trick is to take the position to paint
    //add the tile origin coordinates
    //remove the average of the tile origin coordinates.
    
    //the result is that you will paint the tiles in the
    //configuration in which they have been selected in the
    //tile selector, from the middlemost point
    
    for(int i = 0; i < tileList.count(); i++)
    {
        int paintSpotX = x + tileList[i].first - avgX;
        int paintSpotY = y + tileList[i].second - avgY;
        
        if(preview)
            tiles->PreviewModifyTile(paintSpotX, paintSpotY, tileList[i]);
        else
            tiles->ModifyTile(paintSpotX, paintSpotY, tileList[i]);
    }
}

void StampBrush::CreateGrid(QList<TileCoord> items)
{
    //remove all current items
    tileList.clear();

    avgX = 0;
    avgY = 0;

    //loop through the items and fill the list
    for(int i = 0; i < items.count(); i++)
    {
        //add it into the list of items
        tileList.append(items[i]);
            
        //add its origin points to the tally of origins
        avgX += items[i].first;
        avgY += items[i].second;
    }
    
    if(tileList.count() > 0)
    {
        //create the averages
        avgX = (int)(avgX / tileList.count());
        avgY = (int)(avgY / tileList.count());
    }
    else
    {
        avgX = 0;
        avgY = 0;
    }
}
