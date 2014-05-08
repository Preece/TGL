#include "AddResourceCommand.h"

AddResourceCommand::AddResourceCommand(ObjectNode *newResource, QHash<int, Image *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QHash<int, ObjectNode*>* >(resources);

    invertAdditions = false;
}

AddResourceCommand::AddResourceCommand(ObjectNode *newResource, QHash<int, TileLayer *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QHash<int, ObjectNode*>* >(resources);

    invertAdditions = true;
}

AddResourceCommand::~AddResourceCommand()
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

void AddResourceCommand::undo()
{
    if(resource)
        resourceList->remove(resource->GetID());
}

void AddResourceCommand::redo()
{
    resourceList->insert(resource->GetID(), resource);
}

bool AddResourceCommand::ListContainsResource()
{
    if(resourceList->value(resource->GetID()))
        return true;

    return false;
}
