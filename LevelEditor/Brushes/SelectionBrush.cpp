#include "SelectionBrush.h"

SelectionBrush::SelectionBrush()
{
    selection = new QRubberBand(QRubberBand::Rectangle);

    QPalette palette;
    palette.setBrush(QPalette::Foreground, QBrush(Qt::green));
    palette.setBrush(QPalette::Base, QBrush(Qt::red));

    selection->setPalette(palette);
}

SelectionBrush::~SelectionBrush()
{
    delete selection;
}

void SelectionBrush::Press(int x, int y, TileLayerView *layer)
{
    clickSpot.setX(x);
    clickSpot.setY(y);
}

void SelectionBrush::Move(int x, int y, TileLayerView *layer, bool leftButtonDown)
{
    if(leftButtonDown)
    {
        if(clickSpot.x() == x && clickSpot.y() == y)
            return;

        selection->setGeometry(clickSpot.x(), clickSpot.y(), x - clickSpot.x(), y - clickSpot.y());

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
