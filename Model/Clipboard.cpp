#include "Clipboard.h"

Clipboard::Clipboard(QObject *parent) :
    QObject(parent)
{
}

Clipboard::~Clipboard()
{

}

void Clipboard::Copy(QList<Tile> copyTiles)
{
    tiles = copyTiles;
}

void Clipboard::Paste()
{
    if(tiles.count() > 0)
        emit PasteTiles(tiles);
}
