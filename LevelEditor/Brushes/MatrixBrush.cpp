#include "MatrixBrush.h"

MatrixBrush::MatrixBrush()
{
    AddList(13);
}

void MatrixBrush::Paint(int x, int y, TileLayer *layer, bool preview)
{
    //clear the preview


}

void MatrixBrush::Rect(int x, int y, int w, int h, TileLayer *layer, bool preview)
{
    //paint the interior
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            //paint a middle tile
            if(preview)
                layer->PreviewModifyTile(j + x, i + y, GetRandomTile(4));
            else
                layer->ModifyTile(j + x, i + y, GetRandomTile(4));
        }
    }

    //paint around the edges
    for(signed int i = -1; i <= w; i++)
    {
        if(!ListContainsTile(4, layer->GetTileType(x + i, currentRect.top() - 1)))
            ContextPaintTile(x + i, currentRect.top() - 1, layer, preview);

        //bottom
        if(!ListContainsTile(4, layer->GetTileType(x + i, currentRect.bottom() + 1)))
            ContextPaintTile(x + i, currentRect.bottom() + 1, layer, preview);
    }

    for(signed int i = -1; i <= h; i++)
    {
        //left
        if(!ListContainsTile(4, layer->GetTileType(currentRect.left() - 1, y + i)))
            ContextPaintTile(currentRect.left() - 1, y + i, layer, preview);

        //right
        if(!ListContainsTile(4, layer->GetTileType(currentRect.right() + 1, y + i)))
            ContextPaintTile(currentRect.right() + 1, y + i, layer, preview);
    }
}

void MatrixBrush::Press(int x, int y, TileLayer *layer)
{
    //if it was the left mouse button
    currentRect.setLeft(x);
    currentRect.setTop(y);
    currentRect.setWidth(1);
    currentRect.setHeight(1);

    Rect(x, y, 1, 1, layer, true);
}

void MatrixBrush::Move(int x, int y, TileLayer *layer, bool leftButtonDown)
{
    //if the left mouse is down
    if(leftButtonDown)
    {
        //if the rect is changed
        if(currentRect.right() != x || currentRect.bottom() != y)
        {
            layer->ClearPreview();
            currentRect.setRight(x);
            currentRect.setBottom(y);

            Rect(currentRect.x(), currentRect.y(), currentRect.width(), currentRect.height(), layer, true);
        }
    }
}

void MatrixBrush::Release(int x, int y, TileLayer *layer)
{
    //if it was the left button being released
        //actually draw the line
    Rect(currentRect.x(), currentRect.y(), currentRect.width(), currentRect.height(), layer, false);

    layer->ClearPreview();

    currentRect.setRect(0,0,0,0);
}
