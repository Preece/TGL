#include "TileView.h"

TileView::TileView(QWidget *parent) :
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    maxZoom = false;
    panning = false;

    QGLFormat format;
    format.setSamples(2);
    format.setSampleBuffers(true);
    format.setDepth(false);
    //setViewport(new QGLWidget(format));
    //setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    currentCursor = QCursor(Qt::ArrowCursor);
}

void TileView::SetCursor(QCursor newCursor)
{
    setCursor(newCursor);
    currentCursor = newCursor;
}

void TileView::mouseMoveEvent(QMouseEvent *event)
{
    if (panning)
    {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - clickSpot.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - clickSpot.y()));
        clickSpot = event->pos();
        event->accept();

        dynamic_cast<TileScene*>(scene())->ClearPreview();

        return;
    }
    else
    {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void TileView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->modifiers() == Qt::ControlModifier)
    {
        panning = true;
        clickSpot = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();

        dynamic_cast<TileScene*>(scene())->ClearPreview();

        return;
    }
    else
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void TileView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && panning)
    {
        panning = false;
        setCursor(currentCursor);
        event->accept();
        return;
    }
    else
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void TileView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_F1)
    {
        QMessageBox::information(NULL, "Items in Scene", QString::number(scene()->items().count()));
    }
}

void TileView::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() == Qt::ControlModifier)
    {
        //emit a signal that either the next or previous tiles in the history
        //stack should be selected. This stack should be in the tile selector
        if(event->delta() > 0)
            emit TraverseTileHistory(true);
        else
            emit TraverseTileHistory(false);

        dynamic_cast<TileScene*>(scene())->RefreshPreview();

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

            emit ZoomLevelChanged(transform().m11() * 100);
        }
        else
        {
            maxZoom = true;
        }
    }
    else //zoom out
    {
        if(transform().m11() >= 0.1 && transform().m22() >= 0.1)
        {
            //zoom out
            scale(1/scaleFactor, 1/scaleFactor);
            maxZoom = false;

            emit ZoomLevelChanged(transform().m11() * 100);
        }

        //get the transformed size of the scene in this view
        int sceneWidthInView = transform().m11() * sceneRect().width();
        int sceneHeightInView = transform().m22() * sceneRect().height();

        //if the size of the scene is smaller than the view, or the zoom is 10%
        if(sceneWidthInView <= frameRect().width() && sceneHeightInView <= frameRect().height())
        {
            //make the scene fit nicely in there
            fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
            maxZoom = true;
        }
    }
}

void TileView::drawBackground(QPainter *, const QRectF)
{

}

void TileView::resizeEvent(QResizeEvent *)
{
    if(maxZoom)
        fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void TileView::leaveEvent(QEvent *)
{
    dynamic_cast<TileScene*>(scene())->ClearPreview();
}
