#include "MiniMap.h"

MiniMap::MiniMap(QWidget *parent) :
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    maxZoomed = false;
}

void MiniMap::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void MiniMap::mousePressEvent(QMouseEvent *event)
{
   // QGraphicsView::mousePressEvent(event);
}

void MiniMap::mouseReleaseEvent(QMouseEvent *event)
{
   // QGraphicsView::mouseReleaseEvent(event);
}

void MiniMap::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = 1.15;

    //zoom in
    if(event->delta() > 0)
    {
        //if the zoom is less than 10x, zoom in
        if(transform().m11() <= 10 && transform().m22() <= 10)
        {
            scale(scaleFactor, scaleFactor);
            maxZoomed = false;
        }
        else
        {
            maxZoomed = true;
        }
    }
    else //zoom out
    {
        //zoom out
        scale(1/scaleFactor, 1/scaleFactor);
        maxZoomed = false;

        //get the transformed size of the scene in this view
        int sceneWidthInView = transform().m11() * sceneRect().width();
        int sceneHeightInView = transform().m22() * sceneRect().height();

        //if the size of the scene is smaller than the view
        if(sceneWidthInView <= frameRect().width() && sceneHeightInView <= frameRect().height())
        {
            //make the scene fit nicely in there
            fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
            maxZoomed = true;
        }
    }
}

void MiniMap::drawBackground(QPainter *painter, const QRectF &rect)
{

    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::DashLine);
    painter->drawRect(sceneRect());
}

void MiniMap::resizeEvent(QResizeEvent *event)
{
    if(maxZoomed)
        fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
