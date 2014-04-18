#ifndef MINIMAP_H
#define MINIMAP_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QPoint>
#include <QScrollBar>

class MiniMap : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MiniMap(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void mouseMoveEvent (QMouseEvent * event);
    void mousePressEvent (QMouseEvent * event);
    void mouseReleaseEvent (QMouseEvent * event);
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
    void resizeEvent(QResizeEvent *event);

private:
    bool maxZoomed;

    bool panning;
    QPoint clickSpot;
};

#endif // MINIMAP_H
