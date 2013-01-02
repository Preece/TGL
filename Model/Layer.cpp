#include "Layer.h"

Layer::Layer()
{
}

bool Layer::Export(Exporter *exporter)
{
    exporter->WriteDouble(verticalParallax);
    exporter->WriteDouble(horizontalParallax);
    exporter->WriteString(name);
    exporter->WriteInt(opacity);

    return true;
}

bool Layer::Import(Exporter *exporter)
{
    exporter->ReadDouble(verticalParallax);
    exporter->ReadDouble(horizontalParallax);
    exporter->ReadString(name);
    exporter->ReadInt(opacity);

    return true;
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

    AddChild(tempTile);

    return tempTile;
}

void Layer::RemoveTile(int x, int y)
{
    TileInstance *tempTile;

    for(int i = 0; i < GetChildCount(); i++)
    {
        tempTile = static_cast<TileInstance*>(GetChildByIndex(i));

        //if the tile exists at the specified position, change it
        if(tempTile->GetX() == x && tempTile->GetY() == y)
        {
            RemoveChild(tempTile->GetID());
            return;
        }
    }
}

void Layer::ModifyTile(int x, int y, int ID)
{
    TileInstance *tempTile;

    for(int i = 0; i < GetChildCount(); i++)
    {
        tempTile = static_cast<TileInstance*>(GetChildByIndex(i));

        //if the tile exists at the specified position, change it
        if(tempTile->GetX() == x && tempTile->GetY() == y)
        {
            tempTile->SetTileID(ID);
            return;
        }
    }
}
