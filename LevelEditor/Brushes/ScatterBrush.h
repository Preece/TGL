#ifndef SCATTERBRUSH_H
#define SCATTERBRUSH_H

#include "TileBrush.h"

class ScatterBrush : public TileBrush
{
public:
    ScatterBrush();

    int GetTileCount() { return tiles.count(); }
    int GetTile(int i) { if(i < tiles.count()) return tiles[i]; }
    void RemoveTile(int i) { if(i < tiles.count()) tiles.removeAt(i); }
    void AddTile(int ID) { tiles.append(ID); }

private:
    QList<int> tiles;
};

#endif // SCATTERBRUSH_H
