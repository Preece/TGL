#include "Tile.h"

Tile::Tile()
{
}

bool Tile::Export(Exporter *exporter)
{
    exporter->WriteInt(originX);
    exporter->WriteInt(originY);
    exporter->WriteInt(collision);
    exporter->WriteInt(tilesheetID);

    return false;
}

bool Tile::Import(Exporter *exporter)
{
    exporter->ReadInt(originX);
    exporter->ReadInt(originY);
    exporter->ReadInt(collision);
    exporter->ReadInt(tilesheetID);

    return false;
}
