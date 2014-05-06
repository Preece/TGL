#include "ComplexBrush.h"

ComplexBrush::ComplexBrush()
{
}

ComplexBrush::~ComplexBrush()
{

}

void ComplexBrush::AddList(int count)
{
    for(int i = 0; i < count; i++)
    {
        TileList tempList;
        lists.append(tempList);
    }
}

void ComplexBrush::RemoveList(int index)
{
    if(index < 0 || index >= lists.count())
        return;

    lists.removeAt(index);
}

void ComplexBrush::AddTiles(int listIndex, TileList tiles, bool clear)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return;

    if(clear)
        lists[listIndex].clear();

    for(int i = 0; i < tiles.count(); i++)
    {
        lists[listIndex].append(tiles[i]);
    }
}

TileCoord ComplexBrush::GetTile(int listIndex, int tileIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return TileCoord(-1, -1);

    if(tileIndex < 0 || tileIndex >= lists[listIndex].count())
        return TileCoord(-1, -1);

    return lists[listIndex][tileIndex];
}

TileList ComplexBrush::GetTiles(int listIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
    {
        TileList empty;
        return empty;
    }

    return lists[listIndex];
}

TileCoord ComplexBrush::GetRandomTile(int listIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return TileCoord(-1, -1);

    if(lists[listIndex].count() == 0)
        return TileCoord(-1, -1);

    int rand = qrand() % (lists[listIndex].count());

    return lists[listIndex][rand];
}

int ComplexBrush::GetTileCount(int listIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return 0;

    return lists[listIndex].count();
}

void ComplexBrush::RemoveTile(int listIndex, int tileIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return;

    if(tileIndex < 0 || tileIndex >= lists[listIndex].count())
        return;

    lists[listIndex].removeAt(tileIndex);
}

bool ComplexBrush::IsListEmpty(int listIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return true;

    if(lists[listIndex].count() == 0)
        return true;

    return false;
}

bool ComplexBrush::ListContainsTile(int listIndex, TileCoord origin)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return false;

    for(int i = 0; i < lists[listIndex].count(); i++)
    {
        if(lists[listIndex][i] == origin)
            return true;
    }

    return false;
}
