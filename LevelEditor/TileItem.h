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

    int GetOriginX() { if(tile) return tile->GetXOrigin(); }
    int GetOriginY() { if(tile) return tile->GetYOrigin(); }

private:
    Tile *tile;
};

#endif // TILEITEM_H
