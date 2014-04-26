#include "SelectionBrush.h"

SelectionBrush::SelectionBrush()
{
    dragMode = false;
    clickAfterDrag = false;
}

SelectionBrush::~SelectionBrush()
{
}

void SelectionBrush::Press(int x, int y, TileLayerView *layer)
{
    //later, cut and paste will draw from the tiles suspended in this class.


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
        IntegrateSelectedTiles(layer);
    }
    
    clickSpot.setX(x);
    clickSpot.setY(y);
    previousMouseSpot.setX(x);
    previousMouseSpot.setY(y);
}

void SelectionBrush::Move(int x, int y, TileLayerView *layer, bool leftButtonDown)
{
    if(leftButtonDown)
    {
        //if they are dragging a selection around
        if(dragMode)
        {
            //clear the current preview
            layer->ClearPreview();

            //get the amount of movement
            signed int xDiff = x - previousMouseSpot.x();
            signed int yDiff = y - previousMouseSpot.y();

            //apply the change to the position of each selected item, then draw
            for(int i = 0; i < selectedItems.count(); i++)
            {
                selectedItems[i].pos.first += xDiff;
                selectedItems[i].pos.second += yDiff;
                layer->PreviewModifyTile(selectedItems[i].pos.first, selectedItems[i].pos.second, selectedItems[i].origin);
            }

            layer->SelectPreviewItems();

            previousMouseSpot.setX(x);
            previousMouseSpot.setY(y);
        }
        //if they are not dragging a selection, they are making a new selection
        else
        {
            //so select new stuff
            layer->SelectTilesInArea(QRect(clickSpot, QPoint(x, y)));
        }
    }
}

void SelectionBrush::Release(int x, int y, TileLayerView *layer)
{
    //unset our flag
    dragMode = false;

    //if the list is empty, do nothing
    if(layer->GetSelectedItems().empty())
        return;

    //get a list of selected tiles that are not preview items
    selectedItems = layer->GetSelectedItems();

    //otherwise, remove them all from the layer, and draw them again as previews
    for(int i = 0; i < selectedItems.count(); i++)
    {
        layer->ModifyTileItem(selectedItems[i].pos.first, selectedItems[i].pos.second, TileCoord(-1, -1));
        layer->PreviewModifyTile(selectedItems[i].pos.first, selectedItems[i].pos.second, selectedItems[i].origin);
    }

    //then select the preview items, to maintain visual consistency
    layer->SelectPreviewItems();
}

void SelectionBrush::Deselect(TileLayerView *layer)
{
    IntegrateSelectedTiles(layer);
}

void SelectionBrush::IntegrateSelectedTiles(TileLayerView *layer)
{
    if(selectedItems.empty() || layer == NULL)
        return;

    //for every selected item, draw it onto the layer
    for(int i = 0; i < selectedItems.count(); i++)
    {
        layer->ModifyTileItem(selectedItems[i].pos.first, selectedItems[i].pos.second, selectedItems[i].origin);
    }

    //clear out the selection
    selectedItems.clear();
    layer->ClearPreview();
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
