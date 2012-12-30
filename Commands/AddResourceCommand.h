#ifndef ADDRESOURCECOMMAND_H
#define ADDRESOURCECOMMAND_H

#include <QUndoCommand>

#include "../Model/Savable.h"
#include "../Model/Sprite.h"
#include "../Model/ObjectInstance.h"

class AddResourceCommand : public QUndoCommand
{
public:
    AddResourceCommand(Savable *newResource, QList<Sprite*> *resources);
    AddResourceCommand(Savable *newResource, QList<ObjectInstance*> *resources);
    ~AddResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    Savable *resource;
    QList<Savable*> *resourceList;
};

#endif // ADDRESOURCECOMMAND_H
