#include "TileWidgetItem.h"

TileWidgetItem::TileWidgetItem()
{
    index = 0;
    origin.first = -1;
    origin.second = -1;
}

TileWidgetItem::~TileWidgetItem()
{
}

void TileWidgetItem::SetTilePixmap(QPixmap newPix)
{
    setPixmap(newPix);
}
