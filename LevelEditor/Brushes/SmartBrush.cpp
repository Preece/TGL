#include "SmartBrush.h"

void SmartBrush::Paint(int x, int y, LayerGroup *layer, bool preview)
{
    //erase the previous preview, if we are in preview mode. Get ready for the next
    if(preview)
        layer->ClearPreview();

    //paint the middle tiles. These get painted over everything
    int radius = size;

    //y dimension
    for(signed int i = -radius + 1; i < radius; i++)
    {
        //x dimension
        for(signed int j = -radius + 1; j < radius; j++)
        {
            if(overwrite || layer->GetTileType(j + x, i + y) == 0)
            {
                if(preview)
                    layer->PreviewModifyTile(j + x, i + y, GetRandomTile(4));
                else
                    layer->ModifyTile(j + x, i + y, GetRandomTile(4));
            }
        }
    }

    //paint the surrounding tiles. These do NOT paint over the middle tiles

    //loop for the diameter
    for(int i = -radius + 1; i < radius; i++)
    {
        //midle left
        if(!ListContainsTile(4, layer->GetTileType(x - radius, y + i)))
        {
            if(overwrite || layer->GetTileType(x - radius, y + i) == 0)
            {
                if(preview)
                    layer->PreviewModifyTile(x - radius, y + i, GetRandomTile(3));
                else
                    layer->ModifyTile(x - radius, y + i, GetRandomTile(3));
            }
        }

        //midle right
        if(!ListContainsTile(4, layer->GetTileType(x + radius, y + i)))
        {
            if(overwrite || layer->GetTileType(x + radius, y + i) == 0)
            {
                if(preview)
                    layer->PreviewModifyTile(x + radius, y + i, GetRandomTile(5));
                else
                    layer->ModifyTile(x + radius, y + i, GetRandomTile(5));
            }
        }

        //top middle
        if(!ListContainsTile(4, layer->GetTileType(x + i, y - radius)))
        {
            if(overwrite || layer->GetTileType(x + i, y - radius) == 0)
            {
                if(preview)
                    layer->PreviewModifyTile(x + i, y - radius, GetRandomTile(1));
                else
                    layer->ModifyTile(x + i, y - radius, GetRandomTile(1));
            }
        }

        //bottom middle
        if(!ListContainsTile(4, layer->GetTileType(x + i, y + radius)))
        {
            if(overwrite || layer->GetTileType(x + i, y + radius) == 0)
            {
                if(preview)
                    layer->PreviewModifyTile(x + i, y + radius, GetRandomTile(7));
                else
                    layer->ModifyTile(x + i, y + radius, GetRandomTile(7));
            }
        }
    }

    //top left
    if(!ListContainsTile(4, layer->GetTileType(x - radius, y - radius)))
    {
        if(overwrite || layer->GetTileType(x - radius, y - radius) == 0)
        {
            if(preview)
                layer->PreviewModifyTile(x - radius, y - radius, GetRandomTile(0));
            else
                layer->ModifyTile(x - radius, y - radius, GetRandomTile(0));
        }
    }

    //top right
    if(!ListContainsTile(4, layer->GetTileType(x + radius, y - radius)))
    {
        if(overwrite || layer->GetTileType(x + radius, y - radius) == 0)
        {
            if(preview)
                layer->PreviewModifyTile(x + radius, y - radius, GetRandomTile(2));
            else
                layer->ModifyTile(x + radius, y - radius, GetRandomTile(2));
        }
    }

    //bottom left
    if(!ListContainsTile(4, layer->GetTileType(x - radius, y + radius)))
    {
        if(overwrite || layer->GetTileType(x - radius, y + radius) == 0)
        {
            if(preview)
                layer->PreviewModifyTile(x - radius, y + radius, GetRandomTile(6));
            else
                layer->ModifyTile(x - radius, y + radius, GetRandomTile(6));
        }
    }

    //bottom right
    if(!ListContainsTile(4, layer->GetTileType(x + radius, y + radius)))
    {
        if(overwrite || layer->GetTileType(x + radius, y + radius) == 0)
        {
            if(preview)
                layer->PreviewModifyTile(x + radius, y + radius, GetRandomTile(8));
            else
                layer->ModifyTile(x + radius, y + radius, GetRandomTile(8));
        }
    }
}

SmartBrush::SmartBrush()
{
    AddList(9);
}
