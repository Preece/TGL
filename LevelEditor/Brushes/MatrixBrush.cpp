#include "MatrixBrush.h"

MatrixBrush::MatrixBrush()
{
    AddList(13);
}

void MatrixBrush::Paint(int, int, TileController *, bool)
{
    //clear the preview


}

void MatrixBrush::Rect(int x, int y, int w, int h, TileController *tiles, bool preview)
{
    //paint the interior
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            //paint a middle tile
            if(preview)
                tiles->PreviewModifyTile(j + x, i + y, GetRandomTile(4));
            else
                tiles->ModifyTile(j + x, i + y, GetRandomTile(4));
        }
    }

    //paint around the edges
    for(signed int i = -1; i <= w; i++)
    {
        if(!ListContainsTile(4, tiles->GetTileOrigin(x + i, currentRect.top() - 1)))
            ContextPaintTile(x + i, currentRect.top() - 1, tiles, preview);

        //bottom
        if(!ListContainsTile(4, tiles->GetTileOrigin(x + i, currentRect.bottom() + 1)))
            ContextPaintTile(x + i, currentRect.bottom() + 1, tiles, preview);
    }

    for(signed int i = -1; i <= h; i++)
    {
        //left
        if(!ListContainsTile(4, tiles->GetTileOrigin(currentRect.left() - 1, y + i)))
            ContextPaintTile(currentRect.left() - 1, y + i, tiles, preview);

        //right
        if(!ListContainsTile(4, tiles->GetTileOrigin(currentRect.right() + 1, y + i)))
            ContextPaintTile(currentRect.right() + 1, y + i, tiles, preview);
    }
}

void MatrixBrush::Press(int x, int y, TileController *tiles)
{
    //if it was the left mouse button
    currentRect.setLeft(x);
    currentRect.setTop(y);
    currentRect.setWidth(1);
    currentRect.setHeight(1);

    Rect(x, y, 1, 1, tiles, true);
}

void MatrixBrush::Move(int x, int y, TileController *tiles, bool leftButtonDown)
{
    //if the left mouse is down
    if(leftButtonDown)
    {
        //if the rect is changed
        if(currentRect.right() != x || currentRect.bottom() != y)
        {
            tiles->ClearPreview();
            currentRect.setRight(x);
            currentRect.setBottom(y);

            Rect(currentRect.x(), currentRect.y(), currentRect.width(), currentRect.height(), tiles, true);
        }
    }
}

void MatrixBrush::Release(int, int, TileController *tiles)
{
    //if it was the left button being released
        //actually draw the line
    Rect(currentRect.x(), currentRect.y(), currentRect.width(), currentRect.height(), tiles, false);

    tiles->ClearPreview();

    currentRect.setRect(0,0,0,0);
}
