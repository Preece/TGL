#include "ObjectInstance.h"

bool ObjectInstance::SetPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}


ObjectInstance::ObjectInstance()
{
}

bool ObjectInstance::Export(Exporter *exporter)
{
    return false;
}

bool ObjectInstance::Import(Exporter *exporter)
{
    return false;
}
