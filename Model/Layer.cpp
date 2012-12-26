#include "Layer.h"

Layer::Layer()
{
}

bool Layer::Export(Exporter *exporter)
{
    return false;
}

bool Layer::Import(Exporter *exporter)
{
    return false;
}

TileInstance *Layer::GetTileAtIndex(int index)
{
    if(index < 0 || index >= GetChildCount())
        return NULL;

    return static_cast<TileInstance*>(GetChildByIndex(index));
}

TileInstance *Layer::AddTile(int x, int y, int ID)
{
    TileInstance *tempTile = new TileInstance;
    tempTile->SetX(x);
    tempTile->SetY(y);
    tempTile->SetTileID(ID);

    return tempTile;
}
