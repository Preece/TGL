#ifndef SCATTERBRUSH_H
#define SCATTERBRUSH_H

#include "TileBrush.h"

class ScatterBrush : public TileBrush
{
public:
    void Paint(int x, int y, LayerGroup *layer, bool preview);

    ScatterBrush();

    int GetTileCount() { return tiles.count(); }
    int GetTile(int i) { if(i < tiles.count()) return tiles[i]; }
    void RemoveTile(int i) { if(i < tiles.count()) tiles.removeAt(i); }
    void AddTile(int ID) { tiles.append(ID); }
    int GetRandomTile();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

private:
    QList<int> tiles;

    QString name;
};

#endif // SCATTERBRUSH_H
