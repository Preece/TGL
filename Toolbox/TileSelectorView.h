#ifndef TILESELECTORVIEW_H
#define TILESELECTORVIEW_H

#include <QGraphicsView>
#include <QPoint>
#include <QMouseEvent>

class TileSelectorView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit TileSelectorView(QObject *parent = 0);
    ~TileSelectorView();
    
signals:
    
public slots:

private:

    
};

#endif // TILESELECTORVIEW_H
