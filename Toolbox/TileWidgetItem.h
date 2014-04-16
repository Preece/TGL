#ifndef TILEITEM_H
#define TILEITEM_H

#include <QGraphicsPixmapItem>
#include "../Model/TileLayer.h"

class TileWidgetItem : public QGraphicsPixmapItem
{
public:
    TileWidgetItem();
    ~TileWidgetItem();

    TileWidgetItem(TileWidgetItem &copyItem)
    {
        origin = copyItem.origin;
        index = copyItem.index;
        setPixmap(copyItem.pixmap());
    }

    TileWidgetItem& operator= (const TileWidgetItem &copyItem)
    {
        origin = copyItem.origin;
        index = copyItem.index;
        setPixmap(copyItem.pixmap());
    }

    void SetTilePixmap(QPixmap newPix);

    void SetIndex(int newIndex) { index = newIndex; }
    int GetIndex() { return index; }

    void SetTileOrigin(TileCoord newOrigin) { origin = newOrigin; }
    TileCoord GetTileOrigin() { return origin; }

private:
    TileCoord origin;

    int index;
};

#endif // TILEITEM_H
