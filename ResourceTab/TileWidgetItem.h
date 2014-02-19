#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsPixmapItem>
#include "../Model/TileLayer.h"

class TileWidgetItem : public QGraphicsPixmapItem
{
public:
    TileWidgetItem();

    void SetTile(Tile *newTile) { tile = newTile; }
    Tile *GetTile() { return tile; }

    void SetTilePixmap(QImage spritesheet, int originX, int originY);
    QPixmap GetTilePixmap();

    void SetIndex(int newIndex) { index = newIndex; }
    int GetIndex() { return index; }

private:
    Tile *tile;

    int index;
};

#endif // TILEITEM_H
