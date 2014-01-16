#ifndef TILEGRID_H
#define TILEGRID_H

#include <QList>
#include <QGraphicsItem>

#include "TileItem.h"
#include "TileInstanceItem.h"

typedef QList<int> Row;
typedef QList<Row> Grid;

class TileGrid
{
public:
    TileGrid();

    void ClearGrid();
    //void CreateGrid(QList<QGraphicsItem> items, int width, int height);

private:

    void SetGridSize(int w, int h);

    Grid grid;
};

#endif // TILEGRID_H
