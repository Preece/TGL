#include "Savable.h"

int Savable::newID = 1;

Savable::Savable()
{
    //when the object is created, automatically generate an ID
    ID = GenerateID();
}

void Savable::AddChild(Savable *newChild)
{
    children.append(newChild);
}

Savable *Savable::GetChild(int ID)
{
    for(int i = 0; i < children.count(); i++)
    {
        if(ID == children[i]->GetID())
        {
            return children[i];
        }
    }

    return NULL;
}

Savable *Savable::GetChildByIndex(int i)
{
    if(i < 0 || i >= children.count())
        return NULL;

    return children[i];
}

int Savable::GetChildCount()
{
    return children.count();
}

void Savable::RemoveChild(int ID)
{
    for(int i = 0; i < children.count(); i++)
    {
        if(ID == children[i]->GetID())
        {
            delete children[i];
            children.removeAt(i);
        }
    }
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
