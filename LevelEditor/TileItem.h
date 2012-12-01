#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsPixmapItem>

class TileItem : public QGraphicsPixmapItem
{
public:
    TileItem();

    void SetTilePixmap(QImage spritesheet, int tileX, int tileY, int w, int h);
};

#endif // TILEITEM_H
