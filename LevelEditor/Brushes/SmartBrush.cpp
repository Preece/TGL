#include "SmartBrush.h"

SmartBrush::SmartBrush()
{
    AddList(13);
}

SmartBrush::~SmartBrush()
{

}


void SmartBrush::Paint(int x, int y, TileController *tiles, bool preview)
{
    //erase the previous preview
    tiles->ClearPreview();

    //paint the middle tiles. These get painted over everything
    int radius = size;

    //y dimension
    for(signed int i = -radius + 1; i < radius; i++)
    {
        //x dimension
        for(signed int j = -radius + 1; j < radius; j++)
        {
            if(overwrite || tiles->GetTileOrigin(j + x, i + y) == TileCoord(-1, -1))
            {
                if(preview)
                    tiles->PreviewModifyTile(j + x, i + y, GetRandomTile(4));
                else
                    tiles->ModifyTile(j + x, i + y, GetRandomTile(4));
            }
        }
    }

    //paint the orthogonal edge tiles. These do NOT paint over the middle tiles

    //loop for the diameter
    for(int i = -radius + 1; i < radius; i++)
    {
        //midle left, if the left hand side is not a middle tile
        if(!ListContainsTile(4, tiles->GetTileOrigin(x - radius, y + i)))
        {
            if(overwrite || tiles->GetTileOrigin(x - radius, y + i) == TileCoord(-1, -1))
            {
                ContextPaintTile(x - radius, y + i, tiles, preview);
            }
        }

        //midle right
        if(!ListContainsTile(4, tiles->GetTileOrigin(x + radius, y + i)))
        {
            if(overwrite || tiles->GetTileOrigin(x + radius, y + i) == TileCoord(-1, -1))
            {
                ContextPaintTile(x + radius, y + i, tiles, preview);
            }
        }

        //top middle
        if(!ListContainsTile(4, tiles->GetTileOrigin(x + i, y - radius)))
        {
            if(overwrite || tiles->GetTileOrigin(x + i, y - radius) == TileCoord(-1, -1))
            {
                ContextPaintTile(x + i, y - radius, tiles, preview);
            }
        }

        //bottom middle
        if(!ListContainsTile(4, tiles->GetTileOrigin(x + i, y + radius)))
        {
            if(overwrite || tiles->GetTileOrigin(x + i, y + radius) == TileCoord(-1, -1))
            {
                ContextPaintTile(x + i, y + radius, tiles, preview);
            }
        }
    }

    //paint the corners

    //top left
    if(!ListContainsTile(4, tiles->GetTileOrigin(x - radius, y - radius)))
    {
        if(overwrite || tiles->GetTileOrigin(x - radius, y - radius) == TileCoord(-1, -1))
        {
            ContextPaintTile(x - radius, y - radius, tiles, preview);
        }
    }

    //top right
    if(!ListContainsTile(4, tiles->GetTileOrigin(x + radius, y - radius)))
    {
        if(overwrite || tiles->GetTileOrigin(x + radius, y - radius) == TileCoord(-1, -1))
        {
            ContextPaintTile(x + radius, y - radius, tiles, preview);
        }
    }

    //bottom left
    if(!ListContainsTile(4, tiles->GetTileOrigin(x - radius, y + radius)))
    {
        if(overwrite || tiles->GetTileOrigin(x - radius, y + radius) == TileCoord(-1, -1))
        {
             ContextPaintTile(x - radius, y + radius, tiles, preview);
        }
    }

    //bottom right
    if(!ListContainsTile(4, tiles->GetTileOrigin(x + radius, y + radius)))
    {
        if(overwrite || tiles->GetTileOrigin(x + radius, y + radius) == TileCoord(-1, -1))
        {
            ContextPaintTile(x + radius, y + radius, tiles, preview);
        }
    }
}

void SmartBrush::ContextPaintTile(int x, int y, TileController *tiles, bool preview)
{
    //if this is not a middle tile
    if(!ListContainsTile(4, tiles->GetTileOrigin(x, y)) && !IsListEmpty(4))
    {
        //check for middle tiles that pinch this tile. That means paint a middle tile
        if(ListContainsTile(4, tiles->GetTileOrigin(x - 1, y)) &&
           ListContainsTile(4, tiles->GetTileOrigin(x + 1, y)))
        {
            //make this a middle tile
            if(preview)
                tiles->PreviewModifyTile(x, y, GetRandomTile(4));
            else
                tiles->ModifyTile(x, y, GetRandomTile(4));

            return;
        }

        if(ListContainsTile(4, tiles->GetTileOrigin(x, y - 1)) &&
           ListContainsTile(4, tiles->GetTileOrigin(x, y + 1)))
        {
            if(preview)
                tiles->PreviewModifyTile(x, y, GetRandomTile(4));
            else
                tiles->ModifyTile(x, y, GetRandomTile(4));

            return;
        }

        if(ListContainsTile(4, tiles->GetTileOrigin(x - 1, y - 1)) &&
           ListContainsTile(4, tiles->GetTileOrigin(x + 1, y + 1)))
        {
            if(preview)
                tiles->PreviewModifyTile(x, y, GetRandomTile(4));
            else
                tiles->ModifyTile(x, y, GetRandomTile(4));

            return;
        }

        if(ListContainsTile(4, tiles->GetTileOrigin(x - 1, y + 1)) &&
           ListContainsTile(4, tiles->GetTileOrigin(x + 1, y - 1)))
        {
            if(preview)
                tiles->PreviewModifyTile(x, y, GetRandomTile(4));
            else
                tiles->ModifyTile(x, y, GetRandomTile(4));

            return;
        }
    }

    //check for side tiles

    //left side
    if(ListContainsTile(4, tiles->GetTileOrigin(x + 1, y)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y + 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y - 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x - 1, y))  && !IsListEmpty(3))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(3));
        else
            tiles->ModifyTile(x, y, GetRandomTile(3));

        return;
    }

    //right side
    if(ListContainsTile(4, tiles->GetTileOrigin(x - 1, y)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y + 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y - 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x + 1, y)) && !IsListEmpty(5))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(5));
        else
            tiles->ModifyTile(x, y, GetRandomTile(5));

        return;
    }

    //top side
    if(ListContainsTile(4, tiles->GetTileOrigin(x, y + 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x + 1, y)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x - 1, y)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y - 1)) && !IsListEmpty(1))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(1));
        else
            tiles->ModifyTile(x, y, GetRandomTile(1));

        return;
    }

    //bottom side
    if(ListContainsTile(4, tiles->GetTileOrigin(x, y - 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x + 1, y)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x - 1, y)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y + 1)) && !IsListEmpty(7))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(7));
        else
            tiles->ModifyTile(x, y, GetRandomTile(7));

        return;
    }

    //top left
    if(ListContainsTile(4, tiles->GetTileOrigin(x + 1, y + 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y + 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x + 1, y)) && !IsListEmpty(0))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(0));
        else
            tiles->ModifyTile(x, y, GetRandomTile(0));

        return;
    }

    //top right
    if(ListContainsTile(4, tiles->GetTileOrigin(x - 1, y + 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y + 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x - 1, y)) && !IsListEmpty(2))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(2));
        else
            tiles->ModifyTile(x, y, GetRandomTile(2));

        return;
    }

    //bottom left
    if(ListContainsTile(4, tiles->GetTileOrigin(x + 1, y - 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y - 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x + 1, y)) && !IsListEmpty(6))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(6));
        else
            tiles->ModifyTile(x, y, GetRandomTile(6));

        return;
    }

    //bottom right
    if(ListContainsTile(4, tiles->GetTileOrigin(x - 1, y - 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x, y - 1)) &&
       !ListContainsTile(4, tiles->GetTileOrigin(x - 1, y)) && !IsListEmpty(8))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(8));
        else
            tiles->ModifyTile(x, y, GetRandomTile(8));

        return;
    }

    //top left corner
    if(ListContainsTile(4, tiles->GetTileOrigin(x + 1, y + 1)) &&
       ListContainsTile(4, tiles->GetTileOrigin(x, y + 1)) &&
       ListContainsTile(4, tiles->GetTileOrigin(x + 1, y)) && !IsListEmpty(9))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(9));
        else
            tiles->ModifyTile(x, y, GetRandomTile(9));

        return;
    }

    //top right
    if(ListContainsTile(4, tiles->GetTileOrigin(x - 1, y + 1)) &&
       ListContainsTile(4, tiles->GetTileOrigin(x, y + 1)) &&
       ListContainsTile(4, tiles->GetTileOrigin(x - 1, y)) && !IsListEmpty(10))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(10));
        else
            tiles->ModifyTile(x, y, GetRandomTile(10));

        return;
    }

    //bottom left
    if(ListContainsTile(4, tiles->GetTileOrigin(x + 1, y - 1)) &&
       ListContainsTile(4, tiles->GetTileOrigin(x, y - 1)) &&
       ListContainsTile(4, tiles->GetTileOrigin(x + 1, y)) && !IsListEmpty(11))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(11));
        else
            tiles->ModifyTile(x, y, GetRandomTile(11));

        return;
    }

    //bottom right
    if(ListContainsTile(4, tiles->GetTileOrigin(x - 1, y - 1)) &&
       ListContainsTile(4, tiles->GetTileOrigin(x, y - 1)) &&
       ListContainsTile(4, tiles->GetTileOrigin(x - 1, y)) && !IsListEmpty(12))
    {
        if(preview)
            tiles->PreviewModifyTile(x, y, GetRandomTile(12));
        else
            tiles->ModifyTile(x, y, GetRandomTile(12));

        return;
    }
}


