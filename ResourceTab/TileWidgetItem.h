#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsPixmapItem>
#include "../Model/TileLayer.h"

class TileWidgetItem : public QGraphicsPixmapItem
{
public:
    TileWidgetItem();
    ~TileWidgetItem();

    void SetTile(Tile *newTile) { tile = newTile; }
    Tile *GetTile() { return tile; }

    void SetTilePixmap(QPixmap newPix);
    QPixmap GetTilePixmap();

    void SetIndex(int newIndex) { index = newIndex; }
    int GetIndex() { return index; }

    TileCoord GetTileOrigin();

private:
    Tile *tile;

    int index;
};

#endif // TILEITEM_H
