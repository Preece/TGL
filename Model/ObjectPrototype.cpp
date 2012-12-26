#include "ObjectPrototype.h"

ObjectPrototype::ObjectPrototype()
{
    spriteID = 0;
    objectType = 0;
    behavior = 0;
}

bool ObjectPrototype::Export(Exporter *exporter)
{
    return false;
}

bool ObjectPrototype::Import(Exporter *exporter)
{
    return false;
}
