#include "SelectionBrush.h"

SelectionBrush::SelectionBrush()
{
    dragMode = false;
    clickAfterDrag = false;
}

SelectionBrush::~SelectionBrush()
{
}

void SelectionBrush::Press(int x, int y, ResourceManager *resources)
{
    //if there is a selected tile at this position
    if(SelectedTileAtPos(x, y))
    {
        //flag that we are currently dragging stuff
        dragMode = true;
    }
    //if there is not a selected tile at this position
    else
    {
        //integrate these tiles into the layer
        IntegrateSelectedTiles(resources);
    }
    
    clickSpot.setX(x);
    clickSpot.setY(y);
    previousMouseSpot.setX(x);
    previousMouseSpot.setY(y);
}

void SelectionBrush::Move(int x, int y, ResourceManager *resources, bool leftButtonDown)
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
            for(int i = 0; i < selectedItems.count(); i++)
            {
                selectedItems[i].pos.first += xDiff;
                selectedItems[i].pos.second += yDiff;
                resources->PreviewModifyTile(selectedItems[i].pos.first, selectedItems[i].pos.second, selectedItems[i].origin);
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

void SelectionBrush::Release(int x, int y, ResourceManager *resources)
{
    //unset our flag
    dragMode = false;

    //if the list is empty, do nothing
    if(resources->GetSelectedItems().empty())
        return;

    //get a list of selected tiles that are not preview items
    selectedItems = resources->GetSelectedItems();

    //otherwise, remove them all from the resources, and draw them again as previews
    for(int i = 0; i < selectedItems.count(); i++)
    {
        resources->ModifyTile(selectedItems[i].pos.first, selectedItems[i].pos.second, TileCoord(-1, -1));
        resources->PreviewModifyTile(selectedItems[i].pos.first, selectedItems[i].pos.second, selectedItems[i].origin);
    }

    //then select the preview items, to maintain visual consistency
    resources->SelectPreviewItems();
}

void SelectionBrush::Deselect(ResourceManager *resources)
{
    IntegrateSelectedTiles(resources);
}

void SelectionBrush::IntegrateSelectedTiles(ResourceManager *resources)
{
    if(selectedItems.empty())
        return;

    //for every selected item, draw it onto the layer
    for(int i = 0; i < selectedItems.count(); i++)
    {
        resources->ModifyTile(selectedItems[i].pos.first, selectedItems[i].pos.second, selectedItems[i].origin);
    }

    //clear out the selection
    selectedItems.clear();
    resources->ClearSelection();
    resources->ClearPreview();
}

void SelectionBrush::ClearSelectedTiles()
{
    selectedItems.clear();
}

bool SelectionBrush::SelectedTileAtPos(int x, int y)
{
    TileCoord pos(x, y);

    for(int i = 0; i < selectedItems.count(); i++)
    {
        if(selectedItems[i].pos == pos)
            return true;
    }

    return false;
}
