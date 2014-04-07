#include "MiniMap.h"

MiniMap::MiniMap(QWidget *parent) :
    QGraphicsView(parent)
{
}

void MiniMap::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void MiniMap::mousePressEvent(QMouseEvent *event)
{
}

void MiniMap::mouseReleaseEvent(QMouseEvent *event)
{
}

void MiniMap::wheelEvent(QWheelEvent *event)
{
    int steps = (event->delta() / 8) / 15;

    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    double scaleFactor = 1.15;

    //zoom in
    if(event->delta() > 0)
    {
        scale(scaleFactor, scaleFactor);
    }
    else //zoom out
    {
        scale(1/scaleFactor, 1/scaleFactor);
    }

    event->accept();
}
