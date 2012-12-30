#include "AddResourceCommand.h"

AddResourceCommand::AddResourceCommand(Savable *newResource, QList<Sprite*> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<Savable*>* >(resources);

    invertAdditions = false;
}

AddResourceCommand::AddResourceCommand(Savable *newResource, QList<ObjectInstance *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<Savable*>* >(resources);

    invertAdditions = false;
}

AddResourceCommand::AddResourceCommand(Savable *newResource, QList<ObjectPrototype *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<Savable*>* >(resources);

    invertAdditions = false;
}

AddResourceCommand::AddResourceCommand(Savable *newResource, QList<Image *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<Savable*>* >(resources);

    invertAdditions = false;
}

AddResourceCommand::AddResourceCommand(Savable *newResource, QList<Layer *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<Savable*>* >(resources);

    invertAdditions = true;
}

AddResourceCommand::AddResourceCommand(Savable *newResource, QList<Tile *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<Savable*>* >(resources);

    invertAdditions = false;
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
    if(invertAdditions)
        resourceList->insert(0, resource);
    else
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
