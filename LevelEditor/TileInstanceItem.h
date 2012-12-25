#ifndef TILEINSTANCEITEM_H
#define TILEINSTANCEITEM_H

#include <QGraphicsPixmapItem>

#include "../Model/TileInstance.h"

class TileInstanceItem : public QGraphicsPixmapItem
{
public:
    TileInstanceItem();

    void SetTileInstance(TileInstance *newTile) { tile = newTile; }
    TileInstance *GetTileInstance() { return tile; }

    void SetTilePixmap(QPixmap tilePixmap);

    int GetX() { if(tile) return tile->GetX(); return 0; }
    int GetY() { if(tile) return tile->GetY(); return 0; }
    int GetTileID() { if(tile) return tile->GetTileID(); return 0; }

private:
    TileInstance *tile;
};

#endif // TILEINSTANCEITEM_H
