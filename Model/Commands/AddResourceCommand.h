#ifndef ADDRESOURCECOMMAND_H
#define ADDRESOURCECOMMAND_H

#include <QUndoCommand>

#include "../Image.h"
#include "../TileLayer.h"

class AddResourceCommand : public QUndoCommand
{
public:
    AddResourceCommand(ObjectNode *newResource, QHash<int, Image*> *resources);
    AddResourceCommand(ObjectNode *newResource, QHash<int, TileLayer*> *resources);

    ~AddResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ObjectNode *resource;
    QHash<int, ObjectNode*> *resourceList;

    bool invertAdditions;
};

#endif // ADDRESOURCECOMMAND_H
