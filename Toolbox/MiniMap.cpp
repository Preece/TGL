#include "MiniMap.h"

MiniMap::MiniMap(QWidget *parent) :
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    maxZoomed = false;
    panning = false;
}

void MiniMap::mouseMoveEvent(QMouseEvent *event)
{
    if (panning)
    {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - clickSpot.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - clickSpot.y()));
        clickSpot = event->pos();
        event->accept();
        return;
    }
}

void MiniMap::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        panning = true;
        clickSpot = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
}

void MiniMap::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        panning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
}

void MiniMap::mouseDoubleClickEvent(QMouseEvent *)
{
    emit CenterMinimapOnLevel();
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

void MiniMap::drawBackground(QPainter *painter, const QRectF)
{

    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::DashLine);
    painter->drawRect(sceneRect());
}

void MiniMap::resizeEvent(QResizeEvent *)
{
    if(maxZoomed)
        fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
