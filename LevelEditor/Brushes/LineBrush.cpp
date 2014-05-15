#include "LineBrush.h"

LineBrush::LineBrush()
{
}

void LineBrush::Press(int x, int y, TileController *tiles)
{
    //if it was the left mouse button
    clickPoint.setX(x);
    clickPoint.setY(y);

    Paint(x, y, tiles, true);
}

void LineBrush::Move(int x, int y, TileController *tiles, bool leftButtonDown)
{
    //if the left mouse is down
    if(leftButtonDown)
    {
        tiles->ClearPreview();

        //if the position has changed
        if(movePoint.x() != x || movePoint.y() != y)
        {
            Line(clickPoint.x(), clickPoint.y(), x, y, tiles, true);

            movePoint.setX(x);
            movePoint.setY(y);
        }
    }
}

void LineBrush::Release(int x, int y, TileController *tiles)
{
    //if it was the left button being released
        //actually draw the line
        Line(clickPoint.x(), clickPoint.y(), x, y, tiles);

        tiles->ClearPreview();
}

void LineBrush::Paint(int x, int y, TileController *tiles, bool preview)
{
    //if no tile is selected, bail
    if(selectedTileOrigin == TileCoord(-1, -1))
        return;

    int radius = size;
    int radiusSquared = radius * radius;

    //y dimension
    for(signed int i = -radius; i <= radius; i++)
    {
        int iSquared = i * i;
        //x dimension
        for(signed int j = -radius; j <= radius; j++)
        {
            //constrain to within the radius of the drawing circle
            if((iSquared + (j*j)) < radiusSquared)
            {
                TileCoord currOrigin = tiles->GetTileOrigin(j + x, i + y);

                //and make sure the draw operation would not be painting the same tile.
                //the preview "or" clause is for when eyedropping a tile. the preview wont
                //refresh if you eyedrop, because the model would suggest that it
                //was already the right tile
                if(preview || currOrigin != selectedTileOrigin)
                {
                    //if they have either selected to overwrite other tiles,
                    //or the tile they are painting on is empty
                    if(overwrite || currOrigin == TileCoord(-1, -1))
                    {
                        //paint either a preview or an actual tile
                        if(preview)
                            tiles->PreviewModifyTile(j + x, i + y, selectedTileOrigin);
                        else
                            tiles->ModifyTile(j + x, i + y, selectedTileOrigin);
                    }
                }
            }
        }
    }
}
