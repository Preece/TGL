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
        //pop out all selected tiles and put them in a list
        //flag that we are currently dragging stuff
    clickSpot.setX(x);
    clickSpot.setY(y);
}

void SelectionBrush::Move(int x, int y, TileLayerView *layer, bool leftButtonDown)
{
    if(leftButtonDown)
    {
        if(clickSpot.x() == x && clickSpot.y() == y)
            return;

        layer->SelectTilesInArea(QRect(clickSpot, QPoint(x, y)));
    }
}

void SelectionBrush::Release(int x, int y, TileLayerView *layer)
{
    //get a list of selected tiles that are not preview items
    QList<TileData> selectedItems = layer->GetSelectedItems();

    //if the list is empty, do nothing
    if(selectedItems.empty())
        return;

    //otherwise, remove them all from the layer, and draw them again as previews
    for(int i = 0; i < selectedItems.count(); i++)
    {
        layer->ModifyTileItem(selectedItems.pos.first, selectedItems.pos.second, TileCoord(-1, -1));
        layer->PreviewModifyTile(selectedItems.pos.first, selectedItems.pos.second, selectedItems.origin);
    }

    //then select the preview items, to maintain visual consistency
    layer->SelectPreviewItems();
}

void SelectionBrush::Paint(int x, int y, TileLayerView *layer, bool preview)
{

}
