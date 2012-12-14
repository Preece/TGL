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

    int GetX() { if(tile) return tile->GetX(); }
    int GetY() { if(tile) return tile->GetY(); }
    int GetTileID() { if(tile) return tile->GetTileID(); }

private:
    TileInstance *tile;
};

#endif // TILEINSTANCEITEM_H
