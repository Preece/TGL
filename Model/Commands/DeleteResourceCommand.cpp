#include "DeleteResourceCommand.h"

DeleteResourceCommand::DeleteResourceCommand(ItemNode *newResource, QHash<int, Image *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QHash<int, ItemNode*>* >(resources);
}

DeleteResourceCommand::DeleteResourceCommand(ItemNode *newResource, QHash<int, TileLayer *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QHash<int, ItemNode*>* >(resources);
}

DeleteResourceCommand::~DeleteResourceCommand()
{
    //if the resource is not in the list when this command is destroyed, destroy the resource
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
