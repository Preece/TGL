#include "ObjectPrototype.h"

ObjectPrototype::ObjectPrototype()
{
    spriteID = 0;
    objectType = 0;
    behavior = 0;
}

bool ObjectPrototype::SaveToFile(Exporter *exporter)
{
    return false;
}

bool ObjectPrototype::LoadFromFile(Exporter *exporter)
{
    return false;
}
