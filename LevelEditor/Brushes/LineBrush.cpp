#include "LineBrush.h"

LineBrush::LineBrush()
{
}

void LineBrush::Press(int x, int y, TileLayerView *layer)
{
    //if it was the left mouse button
    clickPoint.setX(x);
    clickPoint.setY(y);

    Paint(x, y, layer, true);
}

void LineBrush::Move(int x, int y, TileLayerView *layer, bool leftButtonDown)
{
    //if the left mouse is down
    if(leftButtonDown)
    {
        //if the position has changed
        if(movePoint.x() != x || movePoint.y() != y)
        {
            layer->ClearPreview();
            Line(clickPoint.x(), clickPoint.y(), x, y, layer, true);

            movePoint.setX(x);
            movePoint.setY(y);
        }
    }
}

void LineBrush::Release(int x, int y, TileLayerView *layer)
{
    //if it was the left button being released
        //actually draw the line
        Line(clickPoint.x(), clickPoint.y(), x, y, layer);

        layer->ClearPreview();
}

void LineBrush::Paint(int x, int y, TileLayerView *layer, bool preview)
{
    //if no tile is selected, bail
    if(selectedTileOrigin == TileCoord(-1, -1))
        return;

    int radius = size;

    //y dimension
    for(signed int i = -radius; i <= radius; i++)
    {
        //x dimension
        for(signed int j = -radius; j <= radius; j++)
        {
            if((i*i) + (j*j) < (radius * radius))
            {
                if(layer->GetTileOrigin(j + x, i + y) != selectedTileOrigin)
                    if(overwrite || layer->GetTileOrigin(j + x, i + y) == TileCoord(-1, -1))
                    {
                        if(preview)
                            layer->PreviewModifyTile(j + x, i + y, selectedTileOrigin);
                        else
                            layer->ModifyTile(j + x, i + y, selectedTileOrigin);
                    }
            }
        }
    }
}
