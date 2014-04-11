#ifndef DELETERESOURCECOMMAND_H
#define DELETERESOURCECOMMAND_H

#include <QUndoCommand>

#include "../ItemNode.h"
#include "../Sprite.h"
#include "../Image.h"
#include "../TileLayer.h"

class DeleteResourceCommand : public QUndoCommand
{
public:
    DeleteResourceCommand(ItemNode *newResource, QHash<int, Sprite*> *resources);
    DeleteResourceCommand(ItemNode *newResource, QHash<int, Image*> *resources);
    DeleteResourceCommand(ItemNode *newResource, QHash<int, TileLayer*> *resources);
    ~DeleteResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ItemNode *resource;
    QHash<int, ItemNode*> *resourceList;
};

#endif // DELETERESOURCECOMMAND_H
