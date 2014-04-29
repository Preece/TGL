#ifndef EYEDROPPERBRUSH_H
#define EYEDROPPERBRUSH_H

#include "TileBrush.h"

class EyedropperBrush : public TileBrush
{
public:
    EyedropperBrush();

    virtual void Press(int x, int y, ResourceManager *resources);
    virtual void Move(int x, int y, ResourceManager *resources, bool leftButtonDown);
    virtual void Release(int x, int y, ResourceManager *resources);

    virtual void Paint(int x, int y, ResourceManager *resources, bool preview = false);

    QString GetType() { return "eyedropper"; }
    QCursor GetCursor() { return QCursor(QPixmap(":/Icons/eyedropper.png"), 14, 14); }
};

#endif // EYEDROPPERBRUSH_H
