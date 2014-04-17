#ifndef SELECTIONBRUSH_H
#define SELECTIONBRUSH_H

#include <QList>
#include <QPoint>
#include <QRubberBand>
#include <QGraphicsScene>

#include "TileBrush.h"

class SelectionBrush : public TileBrush
{
public:
    SelectionBrush();
    ~SelectionBrush();

    virtual void Press(int x, int y, TileLayerView *layer);
    virtual void Move(int x, int y, TileLayerView *layer, bool leftButtonDown);
    virtual void Release(int x, int y, TileLayerView *layer);
    void Paint(int x, int y, TileLayerView *layer, bool preview);

    QString GetType() { return "selection"; }


private:
   QPoint clickSpot;
   QRubberBand *selection;
};

#endif // SELECTIONBRUSH_H
