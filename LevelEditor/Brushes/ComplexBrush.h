#ifndef COMPLEXBRUSH_H
#define COMPLEXBRUSH_H

#include <QList>

#include "TileBrush.h"

typedef QList<int> TileList;

class ComplexBrush : public TileBrush
{
public:
    ComplexBrush();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    void AddList(int count = 1);
    void RemoveList(int index);

    void AddTile(int listIndex, int type);
    int GetTile(int listIndex, int tileIndex);
    int GetRandomTile(int listIndex);
    int GetTileCount(int listIndex);
    void RemoveTile(int listIndex, int tileIndex);

    bool ListContainsTile(int listIndex, int type);

private:
    QList<TileList> lists;

    QString name;
};

#endif // COMPLEXBRUSH_H
