#include "DeleteResourceCommand.h"

DeleteResourceCommand::DeleteResourceCommand(ItemNode *newResource, QList<Sprite*> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<ItemNode*>* >(resources);
}

DeleteResourceCommand::DeleteResourceCommand(ItemNode *newResource, QList<Image *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<ItemNode*>* >(resources);
}

DeleteResourceCommand::DeleteResourceCommand(ItemNode *newResource, QList<TileLayer *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QList<ItemNode*>* >(resources);
}

DeleteResourceCommand::~DeleteResourceCommand()
{
    //if the sprite is not in the list when this command is destroyed, destroy the sprite
    if(!ListContainsResource())
    {
        if(resource)
        {
            delete resource;
            resource = NULL;
        }
    }
}

void DeleteResourceCommand::undo()
{
    resourceList->append(resource);
}

void DeleteResourceCommand::redo()
{
    for(int i = 0; i < resourceList->count(); i++)
    {
        //if this resource is the one being held
        if(resourceList->value(i) == resource)
            resourceList->removeAt(i);
    }
}

bool DeleteResourceCommand::ListContainsResource()
{
    for(int i = 0; i < resourceList->count(); i++)
    {
        if(resourceList->value(i) == resource)
            return true;
    }

    return false;
}
