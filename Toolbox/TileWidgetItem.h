#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsPixmapItem>
#include "../Model/TileLayer.h"

class TileWidgetItem : public QGraphicsPixmapItem
{
public:
    TileWidgetItem();
    ~TileWidgetItem();

    void SetTilePixmap(QPixmap newPix);

    void SetIndex(int newIndex) { index = newIndex; }
    int GetIndex() { return index; }

    void SetTileOrigin(TileCoord newOrigin) { origin = newOrigin; }
    TileCoord GetTileOrigin() { return origin; }

    void SetPosition(TileCoord newPos) { position = newPos; }
    TileCoord GetPosition() { return position; }

private:
    TileCoord origin;
    TileCoord position;

    int index;
};

#endif // TILEITEM_H
