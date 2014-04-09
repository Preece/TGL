#include "AddResourceCommand.h"

AddResourceCommand::AddResourceCommand(ItemNode *newResource, QMap<int, Sprite*> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QMap<int, ItemNode*>* >(resources);

    invertAdditions = false;
}

AddResourceCommand::AddResourceCommand(ItemNode *newResource, QMap<int, Image *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QMap<int, ItemNode*>* >(resources);

    invertAdditions = false;
}

AddResourceCommand::AddResourceCommand(ItemNode *newResource, QMap<int, TileLayer *> *resources)
{
    resource = newResource;
    resourceList = reinterpret_cast<QMap<int, ItemNode*>* >(resources);

    invertAdditions = true;
}

AddResourceCommand::~AddResourceCommand()
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
