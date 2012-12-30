#include "TileInstance.h"

bool TileInstance::Export(Exporter *exporter)
{
    exporter->WriteInt(x);
    exporter->WriteInt(y);
    exporter->WriteInt(tileID);

    return true;
}

bool TileInstance::Import(Exporter *exporter)
{
    exporter->ReadInt(x);
    exporter->ReadInt(y);
    exporter->ReadInt(tileID);

    return false;
}
