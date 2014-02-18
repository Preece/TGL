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
    for(int i = 0; i < tiles.count(); i++)
    {
        if(preview)
            layer->PreviewModifyTile(x + tiles[i].x, y + tiles[i].y, tiles[i].type);
        else
            layer->ModifyTile(x + tiles[i].x, y + tiles[i].y, tiles[i].type);
    }
}

void StampBrush::CreateGrid(QList<QGraphicsItem *> items, int w, int h)
{
    items.clear();

    //loop through the items and fill the list
    for(int i = 0; i < items.count(); i++)
    {
        TilePos tempTile;

    }
}
