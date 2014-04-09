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
    DeleteResourceCommand(ItemNode *newResource, QMap<int, Sprite*> *resources);
    DeleteResourceCommand(ItemNode *newResource, QMap<int, Image*> *resources);
    DeleteResourceCommand(ItemNode *newResource, QMap<int, TileLayer*> *resources);
    ~DeleteResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ItemNode *resource;
    QMap<int, ItemNode*> *resourceList;
};

#endif // DELETERESOURCECOMMAND_H
