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
        if(preview)
            layer->PreviewModifyTile(x + tiles[i].x, y + tiles[i].y, TileCoord(tiles[i].originX, tiles[i].originY));
        else
            layer->ModifyTile(x + tiles[i].x, y + tiles[i].y, TileCoord(tiles[i].originX, tiles[i].originY));
    }
}

void StampBrush::CreateGrid(QList<QGraphicsItem *> items, int w, int h)
{
    tiles.clear();

    //loop through the items and fill the list
    for(int i = 0; i < items.count(); i++)
    {
        //cast the graphics items into a temporary tile item
        TileItem *tempItem = dynamic_cast<TileItem*>(items[i]);
        
        //if the item was casted correctly
        if(tempItem)
            //add it into the list of items
            tiles.append(tempItem);

    }
}
