#include "DeleteResourceCommand.h"

DeleteResourceCommand::DeleteResourceCommand(ItemNode *newResource, QMap<int, Sprite*> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QMap<int, ItemNode*>* >(resources);
}

DeleteResourceCommand::DeleteResourceCommand(ItemNode *newResource, QMap<int, Image *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QMap<int, ItemNode*>* >(resources);
}

DeleteResourceCommand::DeleteResourceCommand(ItemNode *newResource, QMap<int, TileLayer *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QMap<int, ItemNode*>* >(resources);
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
    if(resource)
        resourceList->remove(resource->GetID());
}

void DeleteResourceCommand::redo()
{
    if(resource)
        resourceList->insert(resource->GetID(), resource);
}

bool DeleteResourceCommand::ListContainsResource()
{
    if(resource)
        if(resourceList->value(resource->GetID()))
            return true;

    return false;
}
