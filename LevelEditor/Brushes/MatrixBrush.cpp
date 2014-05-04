#include "MatrixBrush.h"

MatrixBrush::MatrixBrush()
{
    AddList(13);
}

void MatrixBrush::Paint(int, int, ResourceManager *, bool)
{
    //clear the preview


}

void MatrixBrush::Rect(int x, int y, int w, int h, ResourceManager *resources, bool preview)
{
    //paint the interior
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            //paint a middle tile
            if(preview)
                resources->PreviewModifyTile(j + x, i + y, GetRandomTile(4));
            else
                resources->ModifyTile(j + x, i + y, GetRandomTile(4));
        }
    }

    //paint around the edges
    for(signed int i = -1; i <= w; i++)
    {
        if(!ListContainsTile(4, resources->GetTileOrigin(x + i, currentRect.top() - 1)))
            ContextPaintTile(x + i, currentRect.top() - 1, resources, preview);

        //bottom
        if(!ListContainsTile(4, resources->GetTileOrigin(x + i, currentRect.bottom() + 1)))
            ContextPaintTile(x + i, currentRect.bottom() + 1, resources, preview);
    }

    for(signed int i = -1; i <= h; i++)
    {
        //left
        if(!ListContainsTile(4, resources->GetTileOrigin(currentRect.left() - 1, y + i)))
            ContextPaintTile(currentRect.left() - 1, y + i, resources, preview);

        //right
        if(!ListContainsTile(4, resources->GetTileOrigin(currentRect.right() + 1, y + i)))
            ContextPaintTile(currentRect.right() + 1, y + i, resources, preview);
    }
}

void MatrixBrush::Press(int x, int y, ResourceManager *resources)
{
    //if it was the left mouse button
    currentRect.setLeft(x);
    currentRect.setTop(y);
    currentRect.setWidth(1);
    currentRect.setHeight(1);

    Rect(x, y, 1, 1, resources, true);
}

void MatrixBrush::Move(int x, int y, ResourceManager *resources, bool leftButtonDown)
{
    //if the left mouse is down
    if(leftButtonDown)
    {
        //if the rect is changed
        if(currentRect.right() != x || currentRect.bottom() != y)
        {
            resources->ClearPreview();
            currentRect.setRight(x);
            currentRect.setBottom(y);

            Rect(currentRect.x(), currentRect.y(), currentRect.width(), currentRect.height(), resources, true);
        }
    }
}

void MatrixBrush::Release(int, int, ResourceManager *resources)
{
    //if it was the left button being released
        //actually draw the line
    Rect(currentRect.x(), currentRect.y(), currentRect.width(), currentRect.height(), resources, false);

    resources->ClearPreview();

    currentRect.setRect(0,0,0,0);
}
