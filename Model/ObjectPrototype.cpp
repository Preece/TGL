#include "ObjectPrototype.h"

ObjectPrototype::ObjectPrototype()
{
    spriteID = 0;
    type = 0;
    behavior = 0;
}

bool ObjectPrototype::SaveToFile(QFile &file)
{
    return false;
}

bool ObjectPrototype::LoadFromFile(QFile &file)
{
    return false;
}
