#ifndef TILEITEM_H
#define TILEITEM_H

#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsPixmapItem>

#include "../Model/ItemNode.h"

class TileWidgetItem : public QGraphicsPixmapItem
{
public:
    TileWidgetItem();
    ~TileWidgetItem();

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);

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
