#include "AddResourceCommand.h"

AddResourceCommand::AddResourceCommand(Savable *newResource, QList<Sprite*> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<Savable*>* >(resources);
}

AddResourceCommand::AddResourceCommand(Savable *newResource, QList<ObjectInstance *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<Savable*>* >(resources);
}

AddResourceCommand::~AddResourceCommand()
{
    //if the sprite is not in the list when this command is destroyed, destroy the sprite
    if(!ListContainsResource())
    {
        if(resource)
            delete resource;
    }
}

void AddResourceCommand::undo()
{
    for(int i = 0; i < resourceList->count(); i++)
    {
        //if this resource is the one being held
        if(resourceList->value(i) == resource)
            resourceList->removeAt(i);
    }
}

void AddResourceCommand::redo()
{
    resourceList->append(resource);
}

bool AddResourceCommand::ListContainsResource()
{
    for(int i = 0; i < resourceList->count(); i++)
    {
        if(resourceList->value(i) == resource)
            return true;
    }

    return false;
}
