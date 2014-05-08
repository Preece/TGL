#ifndef DELETERESOURCECOMMAND_H
#define DELETERESOURCECOMMAND_H

#include <QUndoCommand>

#include "../Image.h"
#include "../TileLayer.h"

class DeleteResourceCommand : public QUndoCommand
{
public:
    DeleteResourceCommand(ObjectNode *newResource, QHash<int, Image*> *resources);
    DeleteResourceCommand(ObjectNode *newResource, QHash<int, TileLayer*> *resources);
    ~DeleteResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ObjectNode *resource;
    QHash<int, ObjectNode*> *resourceList;
};

#endif // DELETERESOURCECOMMAND_H
