#ifndef LEVELVIEW_H
#define LEVELVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

class LevelView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit LevelView(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void wheelEvent(QWheelEvent *event);
    void drawBackground(QPainter *painter, const QRectF &rect);
};

#endif // LEVELVIEW_H
