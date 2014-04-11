#ifndef ADDRESOURCECOMMAND_H
#define ADDRESOURCECOMMAND_H

#include <QUndoCommand>

#include "../ItemNode.h"
#include "../Sprite.h"
#include "../Image.h"
#include "../TileLayer.h"

class AddResourceCommand : public QUndoCommand
{
public:
    AddResourceCommand(ItemNode *newResource, QHash<int, Sprite*> *resources);
    AddResourceCommand(ItemNode *newResource, QHash<int, Image*> *resources);
    AddResourceCommand(ItemNode *newResource, QHash<int, TileLayer*> *resources);

    ~AddResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ItemNode *resource;
    QHash<int, ItemNode*> *resourceList;

    bool invertAdditions;
};

#endif // ADDRESOURCECOMMAND_H
