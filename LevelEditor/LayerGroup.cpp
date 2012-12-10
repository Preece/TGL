#include "LayerGroup.h"

LayerGroup::LayerGroup()
{
    layerID = 0;
}

void LayerGroup::AddTileInstanceItem(TileInstanceItem *newItem)
{
    items.append(newItem);
    addToGroup(newItem);
}

void LayerGroup::DeleteAllTileInstanceItems()
{
    for(int i = 0; i < items.count(); i++)
    {
        delete items[i];
    }

    items.clear();
}
