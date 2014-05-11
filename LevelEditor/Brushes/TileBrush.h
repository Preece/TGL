#ifndef TILEBRUSH_H
#define TILEBRUSH_H

#include <QPoint>
#include <QCursor>
#include <qmath.h>

#include "../../Model/ResourceController.h"

class TileBrush
{
private:

public:
    TileBrush();
    virtual ~TileBrush();

    virtual void Press(int x, int y, ResourceController *resources);
    virtual void Move(int x, int y, ResourceController *resources, bool leftButtonDown);
    virtual void Release(int, int, ResourceController *);
    virtual void Select(ResourceController *) {}
    virtual void Deselect(ResourceController *) {}

    virtual void Paint(int, int, ResourceController *, bool = false);
    void Line(int x1, int y1, int x2, int y2, ResourceController *resources, bool preview = false);

    virtual QString GetType() = 0;
    virtual QCursor GetCursor() { return QCursor(QPixmap(":/Icons/pencil.png"), 1, 2); }

    void SetSize(int newSize) { size = newSize; }
    void SetOverwrite(bool over) { overwrite = over; }
    void SetSelectedTileOrigin(TileCoord newOrigin) { selectedTileOrigin = newOrigin; }

protected:  
    bool overwrite;

    static int size;
    static TileCoord selectedTileOrigin;

    QPoint lastPaintSpot;
    QPoint lastPreviewSpot;
};

#endif // TILEBRUSH_H
