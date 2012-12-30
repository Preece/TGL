#ifndef ADDRESOURCECOMMAND_H
#define ADDRESOURCECOMMAND_H

#include <QUndoCommand>

#include "../Model/Savable.h"
#include "../Model/Sprite.h"
#include "../Model/ObjectInstance.h"
#include "../Model/ObjectPrototype.h"
#include "../Model/Image.h"
#include "../Model/Layer.h"
#include "../Model/Tile.h"

class AddResourceCommand : public QUndoCommand
{
public:
    AddResourceCommand(Savable *newResource, QList<Sprite*> *resources);
    AddResourceCommand(Savable *newResource, QList<ObjectInstance*> *resources);
    AddResourceCommand(Savable *newResource, QList<ObjectPrototype*> *resources);
    AddResourceCommand(Savable *newResource, QList<Image*> *resources);
    AddResourceCommand(Savable *newResource, QList<Layer*> *resources);
    AddResourceCommand(Savable *newResource, QList<Tile*> *resources);

    ~AddResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    Savable *resource;
    QList<Savable*> *resourceList;

    bool invertAdditions;
};

#endif // ADDRESOURCECOMMAND_H
