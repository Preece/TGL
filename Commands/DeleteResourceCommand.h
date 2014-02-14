#ifndef DELETERESOURCECOMMAND_H
#define DELETERESOURCECOMMAND_H

#include <QUndoCommand>

#include "../Model/Savable.h"
#include "../Model/Sprite.h"
#include "../Model/Image.h"
#include "../Model/Layer.h"
#include "../Model/Tile.h"

class DeleteResourceCommand : public QUndoCommand
{
public:
    DeleteResourceCommand(Savable *newResource, QList<Sprite*> *resources);
    DeleteResourceCommand(Savable *newResource, QList<Image*> *resources);
    DeleteResourceCommand(Savable *newResource, QList<Layer*> *resources);
    DeleteResourceCommand(Savable *newResource, QList<Tile*> *resources);
    ~DeleteResourceCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsResource();

private:
    Savable *resource;
    QList<Savable*> *resourceList;
};

#endif // DELETERESOURCECOMMAND_H
