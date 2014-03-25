#include "TileWidgetItem.h"

TileWidgetItem::TileWidgetItem()
{
    tile = NULL;
    index = 0;
}

TileWidgetItem::~TileWidgetItem()
{
    //if there is a Tile associated
    if(tile)
    {
        //and its x and y are both -1, it is merely used in the selector pane, so destroy it
        if(tile->x == -1 && tile->y == -1)
            delete tile;

    }
}

void TileWidgetItem::SetTilePixmap(QPixmap newPix)
{
    setPixmap(newPix);
}

QPixmap TileWidgetItem::GetTilePixmap()
{
    return pixmap();
}

TileCoord TileWidgetItem::GetTileOrigin()
{
    if(!tile)
        return TileCoord(-1, -1);

    return TileCoord(tile->originX, tile->originY);
}
