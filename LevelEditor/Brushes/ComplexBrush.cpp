#include "ComplexBrush.h"

ComplexBrush::ComplexBrush()
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

void ComplexBrush::AddTile(int listIndex, int type)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return;

    lists[listIndex].append(type);
}

int ComplexBrush::GetTile(int listIndex, int tileIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return -1;

    if(tileIndex < 0 || tileIndex >= lists[listIndex].count())
        return -1;

    return lists[listIndex][tileIndex];
}

int ComplexBrush::GetRandomTile(int listIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return -1;

    if(lists[listIndex].count() == 0)
        return -1;

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

bool ComplexBrush::ListContainsTile(int listIndex, int type)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return false;

    for(int i = 0; i < lists[listIndex].count(); i++)
    {
        if(lists[listIndex][i] == type)
            return true;
    }

    return false;
}
