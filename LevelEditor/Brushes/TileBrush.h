#ifndef TILEBRUSH_H
#define TILEBRUSH_H

#include <QPoint>
#include <qmath.h>

#include "../TileLayer.h"

class TileBrush
{
private:

public:
    TileBrush();

    virtual void Press(int x, int y, TileLayerView *layer);
    virtual void Move(int x, int y, TileLayerView *layer, bool leftButtonDown);
    virtual void Release(int x, int y, TileLayerView *layer);

    virtual void Paint(int x, int y, TileLayerView *layer, bool preview = false);
    void Line(int x1, int y1, int x2, int y2, TileLayerView *layer, bool preview = false);

    virtual QString GetType() = 0;

    void SetSize(int newSize) { size = newSize; }
    void SetOverwrite(bool over) { overwrite = over; }
    void SetSelectedTileID(int newID) { selectedTileID = newID; }

protected:
    static int size;
    bool overwrite;

    static int selectedTileID;

    QPoint lastPaintSpot;
    QPoint lastPreviewSpot;
};

#endif // TILEBRUSH_H
