#ifndef TILEBRUSH_H
#define TILEBRUSH_H

#include <QPoint>
#include <qmath.h>

#include "../LayerGroup.h"

class TileBrush
{
private:

public:
    TileBrush();

    virtual void Paint(int x, int y, LayerGroup *layer, bool preview = false);
    void Line(int x1, int y1, int x2, int y2, LayerGroup *layer);

    virtual QString GetType() = 0;

    void SetSize(int newSize) { size = newSize; }
    void SetOverwrite(bool over) { overwrite = over; }

protected:
    static int size;
    bool overwrite;
};

#endif // TILEBRUSH_H
