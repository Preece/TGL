#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include <QPoint>

#include "TileBrush.h"

class LineBrush : public TileBrush
{
public:
    LineBrush();

    void Press(int x, int y, LayerGroup *layer);
    void Move(int x, int y, LayerGroup *layer, bool leftButtonDown);
    void Release(int x, int y, LayerGroup *layer);

    void Paint(int x, int y, LayerGroup *layer, bool preview);
    QString GetType() { return "line"; }

private:
    QPoint clickPoint;
    QPoint movePoint;
};

#endif // LINEBRUSH_H
