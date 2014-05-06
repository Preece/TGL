#ifndef COMPLEXBRUSH_H
#define COMPLEXBRUSH_H

#include <QList>

#include "TileBrush.h"

typedef QList<TileCoord> TileList;

class ComplexBrush : public TileBrush
{
public:
    ComplexBrush();
    ~ComplexBrush();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    void AddList(int count = 1);
    void RemoveList(int index);

    void AddTile(int listIndex, TileCoord origin);
    void AddTiles(int listIndex, TileList tiles, bool clear = false);
    TileCoord GetTile(int listIndex, int tileIndex);
    TileCoord GetRandomTile(int listIndex);
    int GetTileCount(int listIndex);
    void RemoveTile(int listIndex, int tileIndex);
    bool IsListEmpty(int listIndex);

    bool ListContainsTile(int listIndex, TileCoord origin);

private:
    QList<TileList> lists;

    QString name;
};

#endif // COMPLEXBRUSH_H
