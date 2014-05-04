#ifndef EYEDROPPERBRUSH_H
#define EYEDROPPERBRUSH_H

#include "TileBrush.h"

class EyedropperBrush : public TileBrush
{
public:
    EyedropperBrush();

    virtual void Press(int, int, ResourceManager *);
    virtual void Move(int x, int, ResourceManager *, bool);
    virtual void Release(int, int, ResourceManager *);

    virtual void Paint(int, int, ResourceManager *, bool = false);

    QString GetType() { return "eyedropper"; }
    QCursor GetCursor() { return QCursor(QPixmap(":/Icons/eyedropper.png"), 14, 14); }
};

#endif // EYEDROPPERBRUSH_H
