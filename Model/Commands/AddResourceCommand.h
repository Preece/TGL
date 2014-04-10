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
    AddResourceCommand(ItemNode *newResource, QMap<int, Sprite*> *resources);
    AddResourceCommand(ItemNode *newResource, QMap<int, Image*> *resources);
    AddResourceCommand(ItemNode *newResource, QMap<int, TileLayer*> *resources);

    ~AddResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ItemNode *resource;
    QMap<int, ItemNode*> *resourceList;

    bool invertAdditions;
};

#endif // ADDRESOURCECOMMAND_H
