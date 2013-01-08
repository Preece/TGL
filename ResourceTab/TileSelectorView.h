#ifndef TILESELECTORVIEW_H
#define TILESELECTORVIEW_H

#include <QGraphicsView>
#include <QRubberBand>
#include <QPoint>
#include <QMouseEvent>

class TileSelectorView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TileSelectorView(QObject *parent = 0);
    ~TileSelectorView();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    
signals:
    
public slots:

private:
    QRubberBand *selection;
    QPoint clickSpot;
    
};

#endif // TILESELECTORVIEW_H
