#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsPixmapItem>
#include <Model/Tile.h>

class TileItem : public QGraphicsPixmapItem
{
private:
    int originX, originY;

    Tile *tile;

public:
    TileItem();

    void SetTile(Tile *newTile) { tile = newTile; }
    Tile *GetTile() { return tile; }

    void SetTilePixmap(QImage spritesheet, int tileX, int tileY, int w, int h);
    QPixmap GetTilePixmap();

    int GetOriginX() { return originX; }
    int GetOriginY() { return originY; }
};

#endif // TILEITEM_H
