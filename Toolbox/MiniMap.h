#ifndef MINIMAP_H
#define MINIMAP_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QPoint>
#include <QScrollBar>

#include "../LevelEditor/TileScene.h"

class MiniMap : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MiniMap(QWidget *parent = 0);
    
signals:
    void CenterMinimapOnLevel();

public slots:

protected:
    void mouseMoveEvent (QMouseEvent * event);
    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent (QMouseEvent * event);
    void mouseDoubleClickEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF);
    void resizeEvent(QResizeEvent *);

private:
    bool maxZoomed;

    bool panning;
    QPoint clickSpot;
};

#endif // MINIMAP_H
