#ifndef ADDRESOURCECOMMAND_H
#define ADDRESOURCECOMMAND_H

#include <QUndoCommand>

#include "../Image.h"
#include "../TileLayer.h"

class AddResourceCommand : public QUndoCommand
{
public:
    AddResourceCommand(ResourceNode *newResource, QHash<int, Image*> *resources);
    AddResourceCommand(ResourceNode *newResource, QHash<int, TileLayer*> *resources);

    ~AddResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ResourceNode *resource;
    QHash<int, ResourceNode*> *resourceList;

    bool invertAdditions;
};

#endif // ADDRESOURCECOMMAND_H
