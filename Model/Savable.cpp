#include "Savable.h"

int Savable::newID = 1;

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

bool Savable::WriteString(QFile &file, QString string)
{
    //write out an int that holds the number of letters in the string
    return false;
}
