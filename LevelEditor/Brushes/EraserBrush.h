#ifndef ERASERBRUSH_H
#define ERASERBRUSH_H

#include "TileBrush.h"

class EraserBrush : public TileBrush
{
public:
    EraserBrush();

    void Paint(int x, int y, ResourceManager *resources, bool preview = false);

    QString GetType() { return "eraser"; }
    QCursor GetCursor() { return QCursor(QPixmap(":/Icons/eraser.png"), 2, 5); }

private:
};

#endif // ERASERBRUSH_H
