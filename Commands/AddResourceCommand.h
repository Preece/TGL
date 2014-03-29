#ifndef ADDRESOURCECOMMAND_H
#define ADDRESOURCECOMMAND_H

#include <QUndoCommand>

#include "../Model/ItemNode.h"
#include "../Model/Sprite.h"
#include "../Model/Image.h"
#include "../Model/TileLayer.h"

class AddResourceCommand : public QUndoCommand
{
public:
    AddResourceCommand(ItemNode *newResource, QList<Sprite*> *resources);
    AddResourceCommand(ItemNode *newResource, QList<Image*> *resources);
    AddResourceCommand(ItemNode *newResource, QList<TileLayer*> *resources);

    ~AddResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    ItemNode *resource;
    QList<ItemNode*> *resourceList;

    bool invertAdditions;
};

#endif // ADDRESOURCECOMMAND_H
