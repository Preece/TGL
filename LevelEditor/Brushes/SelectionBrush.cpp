#include "SelectionBrush.h"

SelectionBrush::SelectionBrush()
{
}

SelectionBrush::~SelectionBrush()
{
}

void SelectionBrush::Press(int x, int y, TileLayerView *layer)
{
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
        //if we are dragging tiles around
            //render them in correct position around the mouse

        if(clickSpot.x() == x && clickSpot.y() == y)
            return;

        layer->SelectTilesInArea(QRect(clickSpot, QPoint(x, y)));
    }
}

void SelectionBrush::Release(int x, int y, TileLayerView *layer)
{
    selection->setGeometry(0, 0, 0, 0);
}

void SelectionBrush::Paint(int x, int y, TileLayerView *layer, bool preview)
{

}
