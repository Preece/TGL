#include "MiniMap.h"

MiniMap::MiniMap(QWidget *parent) :
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
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
    double scaleFactor = 1.15;

    //zoom in
    if(event->delta() > 0)
    {
        //if the zoom is less than 10x, zoom in
        if(transform().m11() <= 10 && transform().m22() <= 10)
            scale(scaleFactor, scaleFactor);
    }
    else //zoom out
    {
        //zoom out
        scale(1/scaleFactor, 1/scaleFactor);

        //get the transformed size of the scene in this view
        int sceneWidthInView = transform().m11() * sceneRect().width();
        int sceneHeightInView = transform().m22() * sceneRect().height();

        //if the size of the scene is smaller than the view
        if(sceneWidthInView <= frameRect().width() && sceneHeightInView <= frameRect().height())
        {
            //make the scene fit nicely in there
            fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
        }
    }
}
