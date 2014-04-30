#include "Clipboard.h"

Clipboard::Clipboard(QObject *parent) :
    QObject(parent)
{
}

void Clipboard::Copy(QList<TileData> copyTiles)
{
    tiles = copyTiles;
}

void Clipboard::Paste()
{
    if(tiles.count() > 0)
        emit PasteTiles(tiles);
}
