#ifndef LINEBRUSH_H
#define LINEBRUSH_H

#include <QPoint>

#include "TileBrush.h"

class LineBrush : public TileBrush
{
public:
    LineBrush();

    void Press(int x, int y, ResourceManager *resources);
    void Move(int x, int y, ResourceManager *resources, bool leftButtonDown);
    void Release(int x, int y, ResourceManager *resources);

    void Paint(int x, int y, ResourceManager *resources, bool preview);

    QString GetType() { return "line"; }
    QCursor GetCursor() { return QCursor(QPixmap(":/Icons/line.png"), 1, 1); }

private:
    QPoint clickPoint;
    QPoint movePoint;
};

#endif // LINEBRUSH_H
