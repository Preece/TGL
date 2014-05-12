#include "SelectionBrush.h"

SelectionBrush::SelectionBrush()
{
    dragMode = false;
    clickAfterDrag = false;
}

SelectionBrush::~SelectionBrush()
{
}

void SelectionBrush::Press(int x, int y, TileController *tiles)
{
    if(DraggingTileAtPos(x, y))
    {
        dragMode = true;
    }
    //if there is not a dragged tile at this position
    else
    {
        tiles->SelectTilesInArea(QRect(QPoint(x, y), QPoint(x, y)));

        dragMode = false;
        //integrate these tiles into the layer. This function will
        //do nothing if there are no dragging tiles
        IntegrateDraggingTiles(tiles);
    }
    
    clickSpot.setX(x);
    clickSpot.setY(y);
    previousMouseSpot.setX(x);
    previousMouseSpot.setY(y);
}

void SelectionBrush::Move(int x, int y, TileController *tiles, bool leftButtonDown)
{
    if(leftButtonDown)
    {
        //if they are dragging a selection around
        if(dragMode)
        {
            //clear the current preview
            tiles->ClearPreview();

            //get the amount of movement
            signed int xDiff = x - previousMouseSpot.x();
            signed int yDiff = y - previousMouseSpot.y();

            //apply the change to the position of each selected item, then draw
            for(int i = 0; i < draggingTiles.count(); i++)
            {
                draggingTiles[i].pos.first += xDiff;
                draggingTiles[i].pos.second += yDiff;
                tiles->PreviewModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, draggingTiles[i].origin);
            }

            tiles->SelectPreviewItems();

            previousMouseSpot.setX(x);
            previousMouseSpot.setY(y);
        }
        //if they are not dragging a selection, they are making a new selection
        else
        {
            //so select new stuff
            tiles->SelectTilesInArea(QRect(clickSpot, QPoint(x, y)));
        }
    }
}

void SelectionBrush::Release(int, int, TileController *tiles)
{
    if(!dragMode)
    {
        //first integrate any lingering tiles
        IntegrateDraggingTiles(tiles);

        PopOutSelectedTiles(tiles);
    }

    //select the preview items, to maintain visual consistency
    tiles->SelectPreviewItems();

    dragMode = false;
}

void SelectionBrush::Deselect(TileController *tiles)
{
    IntegrateDraggingTiles(tiles);
}

void SelectionBrush::PopOutSelectedTiles(TileController *tiles)
{
    //get a list of selected tiles that are not preview items
    draggingTiles = tiles->GetSelectedTiles();

    if(!draggingTiles.empty())
    {
        //otherwise, remove them all from the tiles, and draw them again as previews
        for(int i = 0; i < draggingTiles.count(); i++)
        {
            tiles->ModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, TileCoord(-1, -1));
            tiles->PreviewModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, draggingTiles[i].origin);
        }

        tiles->EndPaintOperation();
    }
}

void SelectionBrush::IntegrateDraggingTiles(TileController *tiles)
{
    if(!draggingTiles.empty())
    {
        //for every selected item, draw it onto the layer
        for(int i = 0; i < draggingTiles.count(); i++)
        {
            if(draggingTiles[i].origin != TileCoord(-1, -1))
                tiles->ModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, draggingTiles[i].origin);
        }

        //package this change into an undo operation
        tiles->EndPaintOperation();

        tiles->ClearPreview();
        ClearDraggingTiles();
    }
}

void SelectionBrush::SetDraggingTiles(TileController *tiles, QList<Tile> newTiles)
{
    IntegrateDraggingTiles(tiles);

    draggingTiles = newTiles;

    tiles->ClearPreview();

    if(!draggingTiles.empty())
    {
        //otherwise, remove them all from the tiles, and draw them again as previews
        for(int i = 0; i < draggingTiles.count(); i++)
            tiles->PreviewModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, draggingTiles[i].origin);
    }

    tiles->SelectPreviewItems();
}

void SelectionBrush::ClearDraggingTiles()
{
    draggingTiles.clear();
}

bool SelectionBrush::DraggingTileAtPos(int x, int y)
{
    TileCoord pos(x, y);

    for(int i = 0; i < draggingTiles.count(); i++)
    {
        if(draggingTiles[i].pos == pos)
            return true;
    }

    return false;
}
