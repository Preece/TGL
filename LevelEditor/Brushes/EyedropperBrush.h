#ifndef EYEDROPPERBRUSH_H
#define EYEDROPPERBRUSH_H

#include "TileBrush.h"

class EyedropperBrush : public TileBrush
{
public:
    EyedropperBrush();

    virtual void Press(int, int, ResourceController *);
    virtual void Move(int x, int, ResourceController *, bool);
    virtual void Release(int, int, ResourceController *);

    virtual void Paint(int, int, ResourceController *, bool = false);

    QString GetType() { return "eyedropper"; }
    QCursor GetCursor() { return QCursor(QPixmap(":/Icons/eyedropper.png"), 14, 14); }
};

#endif // EYEDROPPERBRUSH_H
