#ifndef EYEDROPPERBRUSH_H
#define EYEDROPPERBRUSH_H

#include "TileBrush.h"

class EyedropperBrush : public TileBrush
{
public:
    EyedropperBrush();

    virtual void Press(int, int, TileController *);
    virtual void Move(int x, int, TileController *, bool);
    virtual void Release(int, int, TileController *);

    virtual void Paint(int, int, TileController *, bool = false);

    QString GetType() { return "eyedropper"; }
    QCursor GetCursor() { return QCursor(QPixmap(":/Icons/eyedropper.png"), 14, 14); }
};

#endif // EYEDROPPERBRUSH_H
