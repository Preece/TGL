#include "ObjectInstance.h"

bool ObjectInstance::SetPosition(int newX, int newY)
{
    x = newX;
    y = newY;

    return true;
}


ObjectInstance::ObjectInstance()
{
}

bool ObjectInstance::Export(Exporter *exporter)
{
    exporter->WriteInt(prototypeID);
    exporter->WriteInt(x);
    exporter->WriteInt(y);

    return true;
}

bool ObjectInstance::Import(Exporter *exporter)
{
    exporter->ReadInt(prototypeID);
    exporter->ReadInt(x);
    exporter->ReadInt(y);

    return false;
}
