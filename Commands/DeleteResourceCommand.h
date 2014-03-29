#ifndef DELETERESOURCECOMMAND_H
#define DELETERESOURCECOMMAND_H

#include <QUndoCommand>

#include "../Model/ItemNode.h"
#include "../Model/Sprite.h"
#include "../Model/Image.h"
#include "../Model/TileLayer.h"

class DeleteResourceCommand : public QUndoCommand
{
public:
    DeleteResourceCommand(ItemNode *newResource, QList<Sprite*> *resources);
    DeleteResourceCommand(ItemNode *newResource, QList<Image*> *resources);
    DeleteResourceCommand(ItemNode *newResource, QList<TileLayer*> *resources);
    ~DeleteResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ItemNode *resource;
    QList<ItemNode*> *resourceList;
};

#endif // DELETERESOURCECOMMAND_H
