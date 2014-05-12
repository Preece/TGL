#ifndef TILEBRUSH_H
#define TILEBRUSH_H

#include <QPoint>
#include <QCursor>
#include <qmath.h>

#include "../../Model/TileController.h"

class TileBrush
{
private:

public:
    TileBrush();
    virtual ~TileBrush();

    virtual void Press(int x, int y, TileController *tiles);
    virtual void Move(int x, int y, TileController *tiles, bool leftButtonDown);
    virtual void Release(int, int, TileController *);
    virtual void Select(TileController *) {}
    virtual void Deselect(TileController *) {}

    virtual void Paint(int, int, TileController *, bool = false);
    void Line(int x1, int y1, int x2, int y2, TileController *tiles, bool preview = false);

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
