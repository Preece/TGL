#ifndef MINIMAP_H
#define MINIMAP_H

#include <QGraphicsView>

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
    
};

#endif // MINIMAP_H
