#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QtOpenGL>

#include "TileScene.h"

class TileView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TileView(QWidget *parent = 0);

    void SetCursor(QCursor newCursor);
    
signals:
    void TraverseTileHistory(bool forward);

    void ZoomLevelChanged(int newZoom);

public slots:
    void SetZoom(int zoom);

protected:
    void mouseMoveEvent (QMouseEvent * event);
    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent (QMouseEvent * event);
    void keyPressEvent(QKeyEvent *event);

    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *);
    void leaveEvent(QEvent *);

private:
    double zoomLevel;

    bool panning;
    QPoint clickSpot;

    QCursor currentCursor;
};

#endif // LEVELVIEW_H
