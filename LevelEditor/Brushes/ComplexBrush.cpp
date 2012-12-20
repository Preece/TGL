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

int ComplexBrush::GetTile(int listIndex, int tileIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return;

    if(tileIndex < 0 || tileIndex >= lists[listIndex].count())
        return;

    return lists[listIndex][tileIndex];
}

void ComplexBrush::RemoveTile(int listIndex, int tileIndex)
{
    if(listIndex < 0 || listIndex >= lists.count())
        return;

    if(tileIndex < 0 || tileIndex >= lists[listIndex].count())
        return;

    lists[listIndex].removeAt(tileIndex);
}
