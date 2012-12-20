#ifndef COMPLEXBRUSH_H
#define COMPLEXBRUSH_H

#include <QList>

#include "TileBrush.h"

typedef QList<int> TileList;

class ComplexBrush : public TileBrush
{
public:
    ComplexBrush();

    void AddList(int count = 1);
    void RemoveList(int index);

    int GetTile(int listIndex, int tileIndex);
    void RemoveTile(int listIndex, int tileIndex);

private:
    QList<TileList> lists;
};

#endif // COMPLEXBRUSH_H
