#include "TileInstanceItem.h"

TileInstanceItem::TileInstanceItem()
{
}

void TileInstanceItem::SetTilePixmap(QPixmap tilePixmap)
{
    //if the tile is not set, abort
    if(!tile)
        return;

    setPixmap(tilePixmap);
}
