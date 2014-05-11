#include "SelectionBrush.h"

SelectionBrush::SelectionBrush()
{
    dragMode = false;
    clickAfterDrag = false;
}

SelectionBrush::~SelectionBrush()
{
}

void SelectionBrush::Press(int x, int y, ResourceController *resources)
{
    if(DraggingTileAtPos(x, y))
    {
        dragMode = true;
    }
    //if there is not a dragged tile at this position
    else
    {
        resources->SelectTilesInArea(QRect(QPoint(x, y), QPoint(x, y)));

        dragMode = false;
        //integrate these tiles into the layer. This function will
        //do nothing if there are no dragging tiles
        IntegrateDraggingTiles(resources);
    }
    
    clickSpot.setX(x);
    clickSpot.setY(y);
    previousMouseSpot.setX(x);
    previousMouseSpot.setY(y);
}

void SelectionBrush::Move(int x, int y, ResourceController *resources, bool leftButtonDown)
{
    if(leftButtonDown)
    {
        //if they are dragging a selection around
        if(dragMode)
        {
            //clear the current preview
            resources->ClearPreview();

            //get the amount of movement
            signed int xDiff = x - previousMouseSpot.x();
            signed int yDiff = y - previousMouseSpot.y();

            //apply the change to the position of each selected item, then draw
            for(int i = 0; i < draggingTiles.count(); i++)
            {
                draggingTiles[i].pos.first += xDiff;
                draggingTiles[i].pos.second += yDiff;
                resources->PreviewModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, draggingTiles[i].origin);
            }

            resources->SelectPreviewItems();

            previousMouseSpot.setX(x);
            previousMouseSpot.setY(y);
        }
        //if they are not dragging a selection, they are making a new selection
        else
        {
            //so select new stuff
            resources->SelectTilesInArea(QRect(clickSpot, QPoint(x, y)));
        }
    }
}

void SelectionBrush::Release(int, int, ResourceController *resources)
{
    if(!dragMode)
    {
        //first integrate any lingering tiles
        IntegrateDraggingTiles(resources);

        PopOutSelectedTiles(resources);
    }

    //select the preview items, to maintain visual consistency
    resources->SelectPreviewItems();

    dragMode = false;
}

void SelectionBrush::Deselect(ResourceController *resources)
{
    IntegrateDraggingTiles(resources);
}

void SelectionBrush::PopOutSelectedTiles(ResourceController *resources)
{
    //get a list of selected tiles that are not preview items
    draggingTiles = resources->GetSelectedTiles();

    if(!draggingTiles.empty())
    {
        //otherwise, remove them all from the resources, and draw them again as previews
        for(int i = 0; i < draggingTiles.count(); i++)
        {
            resources->ModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, TileCoord(-1, -1));
            resources->PreviewModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, draggingTiles[i].origin);
        }

        resources->EndPaintOperation();
    }
}

void SelectionBrush::IntegrateDraggingTiles(ResourceController *resources)
{
    if(!draggingTiles.empty())
    {
        //for every selected item, draw it onto the layer
        for(int i = 0; i < draggingTiles.count(); i++)
        {
            if(draggingTiles[i].origin != TileCoord(-1, -1))
                resources->ModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, draggingTiles[i].origin);
        }

        //package this change into an undo operation
        resources->EndPaintOperation();

        resources->ClearPreview();
        ClearDraggingTiles();
    }
}

void SelectionBrush::SetDraggingTiles(ResourceController *resources, QList<Tile> newTiles)
{
    IntegrateDraggingTiles(resources);

    draggingTiles = newTiles;

    resources->ClearPreview();

    if(!draggingTiles.empty())
    {
        //otherwise, remove them all from the resources, and draw them again as previews
        for(int i = 0; i < draggingTiles.count(); i++)
            resources->PreviewModifyTile(draggingTiles[i].pos.first, draggingTiles[i].pos.second, draggingTiles[i].origin);
    }

    resources->SelectPreviewItems();
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
