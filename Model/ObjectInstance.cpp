#include "ObjectInstance.h"

bool ObjectInstance::SetPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}


ObjectInstance::ObjectInstance()
{
}

bool ObjectInstance::SaveToFile(Exporter *exporter)
{
    return false;
}

bool ObjectInstance::LoadFromFile(Exporter *exporter)
{
    return false;
}
