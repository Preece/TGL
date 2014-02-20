#include "TileWidgetItem.h"

TileWidgetItem::TileWidgetItem()
{
    tile = NULL;
    index = 0;
}

void TileWidgetItem::SetTilePixmap(QPixmap newPix)
{
    setPixmap(newPix);
}

QPixmap TileWidgetItem::GetTilePixmap()
{
    return pixmap();
}
