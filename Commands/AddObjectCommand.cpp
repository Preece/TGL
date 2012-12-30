#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(ObjectInstance *newObject, QList<ObjectInstance *> *objects)
{
    object = newObject;
    objectList = objects;
}

AddObjectCommand::~AddObjectCommand()
{
    //if the sprite is not in the list when this command is destroyed, destroy the sprite
    if(!ListContainsObject())
    {
        if(object)
            delete object;
    }
}

void AddObjectCommand::undo()
{
    for(int i = 0; i < objectList->count(); i++)
    {
        //if this sprite is the one being held
        if(objectList->value(i) == object)
            objectList->removeAt(i);
    }
}

void AddObjectCommand::redo()
{
    objectList->append(object);
}

bool AddObjectCommand::ListContainsObject()
{
    for(int i = 0; i < objectList->count(); i++)
    {
        if(objectList->value(i) == object)
            return true;
    }

    return false;
}
