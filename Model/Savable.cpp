#include "Savable.h"

int Savable::newID = 0;

Savable::Savable()
{
    //when the object is created, automatically generate an ID
    ID = GenerateID();
}

int Savable::GenerateID()
{
    return newID++;
}

void Savable::RegisterID(int registeredID)
{
    //loop and increase the newID value until it is bigger than the
    //ID being registered
    while(registeredID >= newID)
        newID++;
}
