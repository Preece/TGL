#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QtOpenGL>

#include "LayerManager.h"

class LevelView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit LevelView(QWidget *parent = 0);

    void SetCursor(QCursor newCursor);
    
signals:
    void TraverseTileHistory(bool forward);

protected:
    void mouseMoveEvent (QMouseEvent * event);
    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent (QMouseEvent * event);

    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void resizeEvent(QResizeEvent *event);
    void leaveEvent(QEvent *event);

private:
    bool maxZoom;

    bool panning;
    QPoint clickSpot;

    QCursor currentCursor;
};

#endif // LEVELVIEW_H
