#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsPixmapItem>
#include <Model/Tile.h>
#include "../Model/TileInstance.h"

class TileItem : public QGraphicsPixmapItem
{
public:
    TileItem();

    void SetTile(Tile *newTile) { tile = newTile; }
    Tile *GetTile() { return tile; }

    void SetTilePixmap(QImage spritesheet, int w, int h);
    QPixmap GetTilePixmap();

    int GetTileID() { if(tile) return tile->GetID(); return 0; }

    void SetIndex(int newIndex) { index = newIndex; }
    int GetIndex() { return index; }

private:
    Tile *tile;

    int index;
};

#endif // TILEITEM_H
