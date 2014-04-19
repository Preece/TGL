#include "LevelView.h"

LevelView::LevelView(QWidget *parent) :
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    maxZoom = false;
    panning = false;

    QGLFormat format;
    format.setSamples(2);
    format.setSampleBuffers(true);
    format.setDepth(false);
    setViewport(new QGLWidget(format));
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void LevelView::SetCursor(TileBrush *, QCursor newCursor)
{
    setCursor(newCursor);
}

void LevelView::mouseMoveEvent(QMouseEvent *event)
{
    if (panning)
    {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - clickSpot.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - clickSpot.y()));
        clickSpot = event->pos();
        event->accept();

        dynamic_cast<LayerManager*>(scene())->ClearPreview();

        return;
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void LevelView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier)
    {
        panning = true;
        clickSpot = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();

        dynamic_cast<LayerManager*>(scene())->ClearPreview();

        return;
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void LevelView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && panning)
    {
        panning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void LevelView::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        //emit a signal that either the next or previous tiles in the history
        //stack should be selected. This stack should be in the tile selector
        return;
    }

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

}

void LevelView::resizeEvent(QResizeEvent *event)
{
    if(maxZoom)
        fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}
