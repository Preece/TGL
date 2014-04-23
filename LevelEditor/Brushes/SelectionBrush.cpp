#include "SelectionBrush.h"

SelectionBrush::SelectionBrush()
{
    dragMode = false;
}

SelectionBrush::~SelectionBrush()
{
}

void SelectionBrush::Press(int x, int y, TileLayerView *layer)
{
    //once tiles are selected and the mouse is released, all selected tiles
    //will be popped out into a list contained within this class, and drag mode
    //will be activated. While in drag mode, all tiles are rendered to the preview,
    //not the actual layer. If the user clicks outside of the selection, all current
    //tiles in the list are integrated back into the actual layer by drawing
    //them normally, and drag mode is deactivated. If they click within the selected 
    //tiles, moving the mouse will drag the selection around.

    //later, cut and paste will draw from the tiles suspended in this class.


    //if there is a selected tile at this position
    if(SelectedTileAtPos(x, y))
    {
        //flag that we are currently dragging stuff
        dragMode = true;
    }
    else
    {
        IntegrateSelectedTiles(layer);
    }
    
    clickSpot.setX(x);
    clickSpot.setY(y);
}

void SelectionBrush::Move(int x, int y, TileLayerView *layer, bool leftButtonDown)
{
    if(leftButtonDown)
    {
        //check that there was actual movement
        if(clickSpot.x() == x && clickSpot.y() == y)
                return;

        //if they are dragging a selection around
        if(dragMode)
        {
            //clear the current preview
            layer->ClearPreview();

            //get the amount of movement
            signed int xDiff = x - clickSpot.x();
            signed int yDiff = y - clickSpot.y();

            //apply the change to the position of each selected item, then draw
            for(int i = 0; i < selectedItems.count(); i++)
            {
                selectedItems[i].pos.first += xDiff;
                selectedItems[i].pos.second += yDiff;
                layer->PreviewModifyTile(selectedItems[i].pos.first, selectedItems[i].pos.second, selectedItems[i].origin);
            }
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
    //unset the dragging flag
    dragMode = false;

    //get a list of selected tiles that are not preview items
    selectedItems = layer->GetSelectedItems();

    //if the list is empty, do nothing
    if(selectedItems.empty())
        return;

    //otherwise, remove them all from the layer, and draw them again as previews
    for(int i = 0; i < selectedItems.count(); i++)
    {
        layer->ModifyTileItem(selectedItems[i].pos.first, selectedItems[i].pos.second, TileCoord(-1, -1));
        layer->PreviewModifyTile(selectedItems[i].pos.first, selectedItems[i].pos.second, selectedItems[i].origin);
    }

    //then select the preview items, to maintain visual consistency
    layer->SelectPreviewItems();
}

void SelectionBrush::Paint(int x, int y, TileLayerView *layer, bool preview)
{

}

void SelectionBrush::IntegrateSelectedTiles(TileLayerView *layer)
{
    if(selectedItems.empty())
        return;

    //for every selected item, draw it onto the layer
    for(int i = 0; i < selectedItems.count(); i++)
    {
        layer->ModifyTileItem(selectedItems[i].pos.first, selectedItems[i].pos.second, selectedItems[i].origin);
    }

    //clear out the selection
    selectedItems.clear();
}

bool SelectionBrush::SelectedTileAtPos(int x, int y)
{
    TileCoord pos(x, y);

    for(int i = 0; i < selectedItems.count(), i++)
    {
        if(selectedItems[i].pos == pos)
            return true;
    }

    return false;
}