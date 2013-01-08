#include "TileSelectorView.h"

TileSelectorView::TileSelectorView(QObject *parent)
{
    selection = new QRubberBand(QRubberBand::Rectangle, this);
}

TileSelectorView::~TileSelectorView()
{
    delete selection;
}

void TileSelectorView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        clickSpot = event->pos();
    }
}

void TileSelectorView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    if(event->buttons() & Qt::LeftButton)
    {
        selection->setGeometry(clickSpot.x(), clickSpot.y(),
                               event->pos().x() - clickSpot.x(), event->pos().y() - clickSpot.y());

        QPainterPath path;
        path.addRect(clickSpot.x(), clickSpot.y(),
                     event->pos().x() - clickSpot.x(), event->pos().y() - clickSpot.y());
        this->scene()->setSelectionArea(path);
    }
}

void TileSelectorView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        selection->setGeometry(0, 0, 0, 0);
    }
}
