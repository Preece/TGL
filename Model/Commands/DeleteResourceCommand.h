#ifndef DELETERESOURCECOMMAND_H
#define DELETERESOURCECOMMAND_H

#include <QUndoCommand>

#include "../Image.h"
#include "../TileLayer.h"

class DeleteResourceCommand : public QUndoCommand
{
public:
    DeleteResourceCommand(ResourceNode *newResource, QHash<int, Image*> *resources);
    DeleteResourceCommand(ResourceNode *newResource, QHash<int, TileLayer*> *resources);
    ~DeleteResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ResourceNode *resource;
    QHash<int, ResourceNode*> *resourceList;
};

#endif // DELETERESOURCECOMMAND_H
