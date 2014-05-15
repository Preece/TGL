#include "TileView.h"

TileView::TileView(QWidget *parent) :
    QGraphicsView(parent)
{
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    panning = false;

    //varies between 1 and 20 (10% - 1,000%)
    zoomLevel = 10;

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

void TileView::SetZoom(int zoom)
{
    if(zoom >= 20 || zoom < 1)
        return;

    zoomLevel = zoom;

    //reset the zoom
    setTransform(QTransform());

    if(zoomLevel < 10)
        scale(zoomLevel / 10, zoomLevel / 10);
    else if(zoomLevel > 10)
        scale(zoomLevel - 9, zoomLevel - 9);
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

    //zoom in
    if(event->delta() > 0)
    {
        SetZoom(zoomLevel + 1);
    }
    else //zoom out
    {
        SetZoom(zoomLevel - 1);
    }

    emit ZoomLevelChanged(zoomLevel);
}

void TileView::drawBackground(QPainter *, const QRectF)
{

}

void TileView::resizeEvent(QResizeEvent *)
{
    //if(maxZoom)
       // fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
}

void TileView::leaveEvent(QEvent *)
{
    dynamic_cast<TileScene*>(scene())->ClearPreview();
}
