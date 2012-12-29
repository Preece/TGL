#include "TileItem.h"

TileItem::TileItem()
{
    tile = NULL;
    index = 0;
}

void TileItem::SetTilePixmap(QImage spritesheet, int w, int h)
{
    //if the tile is not set, abort
    if(!tile)
        return;

    //create an image from the tileset, representing this single tile
    QImage tempImage;
    tempImage = spritesheet.copy((tile->GetXOrigin() * w), (tile->GetYOrigin() * h), w, h);

    setPixmap(QPixmap::fromImage(tempImage));
}

QPixmap TileItem::GetTilePixmap()
{
    return pixmap();
}
