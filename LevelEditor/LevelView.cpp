#include "LevelView.h"

LevelView::LevelView(QWidget *parent) :
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    maxZoom = false;
}

void LevelView::wheelEvent(QWheelEvent *event)
{
    double scaleFactor = 1.15;

    //zoom in
    if(event->delta() > 0)
    {
        //if the zoom is less than 10x, zoom in
        if(transform().m11() <= 10 && transform().m22() <= 10)
        {
            scale(scaleFactor, scaleFactor);
            maxZoom = false;
        }
        else
        {
            maxZoom = true;
        }
    }
    else //zoom out
    {
        //zoom out
        scale(1/scaleFactor, 1/scaleFactor);
        maxZoom = false;

        //get the transformed size of the scene in this view
        int sceneWidthInView = transform().m11() * sceneRect().width();
        int sceneHeightInView = transform().m22() * sceneRect().height();

        //if the size of the scene is smaller than the view
        if(sceneWidthInView <= frameRect().width() && sceneHeightInView <= frameRect().height())
        {
            //make the scene fit nicely in there
            fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
            maxZoom = true;
        }
    }
}

void LevelView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);

    painter->setPen(Qt::DashLine);
    painter->drawRect(sceneRect());
}

void LevelView::resizeEvent(QResizeEvent *event)
{
    if(maxZoom)
        fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
