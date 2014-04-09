#include "TileWidgetItem.h"

TileWidgetItem::TileWidgetItem()
{
    index = 0;
    origin.x = -1;
    origin.y = -1;
}

TileWidgetItem::~TileWidgetItem()
{
}

void TileWidgetItem::SetTilePixmap(QPixmap newPix)
{
    setPixmap(newPix);
}
