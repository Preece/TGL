#include "StampBrush.h"

StampBrush::StampBrush()
{
}

void StampBrush::Move(int x, int y, TileLayerView *layer, bool leftButtonDown)
{
    layer->ClearPreview();

    Paint(x, y, layer, true);
}

void StampBrush::Paint(int x, int y, TileLayerView *layer, bool preview)
{
    //the trick is to take the position to paint
    //add the tile origin coordinates
    //remove the average of the tile origin coordinates.
    
    //the result is that you will paint the tiles in the
    //configuration in which they have been selected in the
    //tile selector, from the middlemost point
    
    for(int i = 0; i < tiles.count(); i++)
    {
        int paintSpotX = x + tiles[i]->GetTileOrigin().first - avgX;
        int paintSpotY = y + tiles[i]->GetTileOrigin().second - avgY;
        
        if(preview)
            layer->PreviewModifyTile(paintSpotX, paintSporY, tiles[i]->GetTileOrigin());
        else
            layer->ModifyTile(paintSpotX, paintSpotY, TileCoord(tiles[i].originX, tiles[i].originY));
    }
}

void StampBrush::CreateGrid(QList<QGraphicsItem *> items, int w, int h)
{
    //remove all current items
    tiles.clear();

    //loop through the items and fill the list
    for(int i = 0; i < items.count(); i++)
    {
        //cast the graphics items into a temporary tile item
        TileWidgetItem *tempItem = dynamic_cast<TileWidgetItem*>(items[i]);
        
        //if the item was casted correctly
        if(tempItem)
        {
            //add it into the list of items
            tiles.append(tempItem);
            
            //add its origin points to the tally of origins
            avgX += tempItem->GetTileOrigin().first;
            avgY += tempItem->GetTileorigin().second;
        }

    }
    
    //create the averages
    avgX = (int)(avgX / tiles.count());
    avgY = (int)(avgY / tiles.count());
}
