#ifndef MINIMAP_H
#define MINIMAP_H

#include <QGraphicsView>
#include <QWheelEvent>

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
    
};

#endif // MINIMAP_H
