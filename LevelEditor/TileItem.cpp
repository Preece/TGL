#include "TileItem.h"

TileItem::TileItem()
{
}

void TileItem::SetTilePixmap(QImage spritesheet, int tileX, int tileY, int w, int h)
{
    QImage tempImage;
    tempImage = spritesheet.copy((tileX * w), (tileY * h), w, h);

    setPixmap(QPixmap::fromImage(tempImage));
}
