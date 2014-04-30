#include "Clipboard.h"

Clipboard::Clipboard()
{

}

Clipboard::~Clipboard()
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
