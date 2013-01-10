#include "MatrixBrush.h"

MatrixBrush::MatrixBrush()
{
    AddList(13);
}

void MatrixBrush::Paint(int x, int y, LayerGroup *layer, bool preview)
{
    //clear the preview


}

void MatrixBrush::Rect(int x, int y, int w, int h, LayerGroup *layer, bool preview)
{
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
}

void MatrixBrush::Press(int x, int y, LayerGroup *layer)
{
    //if it was the left mouse button
    currentRect.setLeft(x);
    currentRect.setTop(y);
    currentRect.setWidth(1);
    currentRect.setHeight(1);

    Rect(x, y, 1, 1, layer, true);
}

void MatrixBrush::Move(int x, int y, LayerGroup *layer, bool leftButtonDown)
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

void MatrixBrush::Release(int x, int y, LayerGroup *layer)
{
    //if it was the left button being released
        //actually draw the line
    Rect(currentRect.x(), currentRect.y(), currentRect.width(), currentRect.height(), layer, false);

    layer->ClearPreview();

    currentRect.setRect(0,0,0,0);
}

void MatrixBrush::ContextPaintTile(int x, int y, LayerGroup *layer, bool preview)
{
    //if this is not a middle tile
    if(!ListContainsTile(4, layer->GetTileType(x, y)) && !IsListEmpty(4))
    {
        //check for middle tiles that pinch this tile. That means paint a middle tile
        if(ListContainsTile(4, layer->GetTileType(x - 1, y)) &&
           ListContainsTile(4, layer->GetTileType(x + 1, y)))
        {
            //make this a middle tile
            if(preview)
                layer->PreviewModifyTile(x, y, GetRandomTile(4));
            else
                layer->ModifyTile(x, y, GetRandomTile(4));

            return;
        }

        if(ListContainsTile(4, layer->GetTileType(x, y - 1)) &&
           ListContainsTile(4, layer->GetTileType(x, y + 1)))
        {
            if(preview)
                layer->PreviewModifyTile(x, y, GetRandomTile(4));
            else
                layer->ModifyTile(x, y, GetRandomTile(4));

            return;
        }

        if(ListContainsTile(4, layer->GetTileType(x - 1, y - 1)) &&
           ListContainsTile(4, layer->GetTileType(x + 1, y + 1)))
        {
            if(preview)
                layer->PreviewModifyTile(x, y, GetRandomTile(4));
            else
                layer->ModifyTile(x, y, GetRandomTile(4));

            return;
        }

        if(ListContainsTile(4, layer->GetTileType(x - 1, y + 1)) &&
           ListContainsTile(4, layer->GetTileType(x + 1, y - 1)))
        {
            if(preview)
                layer->PreviewModifyTile(x, y, GetRandomTile(4));
            else
                layer->ModifyTile(x, y, GetRandomTile(4));

            return;
        }
    }

    //check for side tiles

    //left side
    if(ListContainsTile(4, layer->GetTileType(x + 1, y)) &&
       !ListContainsTile(4, layer->GetTileType(x, y + 1)) &&
       !ListContainsTile(4, layer->GetTileType(x, y - 1)) &&
       !ListContainsTile(4, layer->GetTileType(x - 1, y))  && !IsListEmpty(3))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(3));
        else
            layer->ModifyTile(x, y, GetRandomTile(3));

        return;
    }

    //right side
    if(ListContainsTile(4, layer->GetTileType(x - 1, y)) &&
       !ListContainsTile(4, layer->GetTileType(x, y + 1)) &&
       !ListContainsTile(4, layer->GetTileType(x, y - 1)) &&
       !ListContainsTile(4, layer->GetTileType(x + 1, y)) && !IsListEmpty(5))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(5));
        else
            layer->ModifyTile(x, y, GetRandomTile(5));

        return;
    }

    //top side
    if(ListContainsTile(4, layer->GetTileType(x, y + 1)) &&
       !ListContainsTile(4, layer->GetTileType(x + 1, y)) &&
       !ListContainsTile(4, layer->GetTileType(x - 1, y)) &&
       !ListContainsTile(4, layer->GetTileType(x, y - 1)) && !IsListEmpty(1))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(1));
        else
            layer->ModifyTile(x, y, GetRandomTile(1));

        return;
    }

    //bottom side
    if(ListContainsTile(4, layer->GetTileType(x, y - 1)) &&
       !ListContainsTile(4, layer->GetTileType(x + 1, y)) &&
       !ListContainsTile(4, layer->GetTileType(x - 1, y)) &&
       !ListContainsTile(4, layer->GetTileType(x, y + 1)) && !IsListEmpty(7))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(7));
        else
            layer->ModifyTile(x, y, GetRandomTile(7));

        return;
    }

    //top left
    if(ListContainsTile(4, layer->GetTileType(x + 1, y + 1)) &&
       !ListContainsTile(4, layer->GetTileType(x, y + 1)) &&
       !ListContainsTile(4, layer->GetTileType(x + 1, y)) && !IsListEmpty(0))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(0));
        else
            layer->ModifyTile(x, y, GetRandomTile(0));

        return;
    }

    //top right
    if(ListContainsTile(4, layer->GetTileType(x - 1, y + 1)) &&
       !ListContainsTile(4, layer->GetTileType(x, y + 1)) &&
       !ListContainsTile(4, layer->GetTileType(x - 1, y)) && !IsListEmpty(2))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(2));
        else
            layer->ModifyTile(x, y, GetRandomTile(2));

        return;
    }

    //bottom left
    if(ListContainsTile(4, layer->GetTileType(x + 1, y - 1)) &&
       !ListContainsTile(4, layer->GetTileType(x, y - 1)) &&
       !ListContainsTile(4, layer->GetTileType(x + 1, y)) && !IsListEmpty(6))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(6));
        else
            layer->ModifyTile(x, y, GetRandomTile(6));

        return;
    }

    //bottom right
    if(ListContainsTile(4, layer->GetTileType(x - 1, y - 1)) &&
       !ListContainsTile(4, layer->GetTileType(x, y - 1)) &&
       !ListContainsTile(4, layer->GetTileType(x - 1, y)) && !IsListEmpty(8))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(8));
        else
            layer->ModifyTile(x, y, GetRandomTile(8));

        return;
    }

    //top left corner
    if(ListContainsTile(4, layer->GetTileType(x + 1, y + 1)) &&
       ListContainsTile(4, layer->GetTileType(x, y + 1)) &&
       ListContainsTile(4, layer->GetTileType(x + 1, y)) && !IsListEmpty(9))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(9));
        else
            layer->ModifyTile(x, y, GetRandomTile(9));

        return;
    }

    //top right
    if(ListContainsTile(4, layer->GetTileType(x - 1, y + 1)) &&
       ListContainsTile(4, layer->GetTileType(x, y + 1)) &&
       ListContainsTile(4, layer->GetTileType(x - 1, y)) && !IsListEmpty(10))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(10));
        else
            layer->ModifyTile(x, y, GetRandomTile(10));

        return;
    }

    //bottom left
    if(ListContainsTile(4, layer->GetTileType(x + 1, y - 1)) &&
       ListContainsTile(4, layer->GetTileType(x, y - 1)) &&
       ListContainsTile(4, layer->GetTileType(x + 1, y)) && !IsListEmpty(11))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(11));
        else
            layer->ModifyTile(x, y, GetRandomTile(11));

        return;
    }

    //bottom right
    if(ListContainsTile(4, layer->GetTileType(x - 1, y - 1)) &&
       ListContainsTile(4, layer->GetTileType(x, y - 1)) &&
       ListContainsTile(4, layer->GetTileType(x - 1, y)) && !IsListEmpty(12))
    {
        if(preview)
            layer->PreviewModifyTile(x, y, GetRandomTile(12));
        else
            layer->ModifyTile(x, y, GetRandomTile(12));

        return;
    }
}
