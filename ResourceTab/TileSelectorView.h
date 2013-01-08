#ifndef TILESELECTORVIEW_H
#define TILESELECTORVIEW_H

#include <QGraphicsView>

class TileSelectorView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TileSelectorView(QObject *parent = 0);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    
signals:
    
public slots:
    
};

#endif // TILESELECTORVIEW_H
