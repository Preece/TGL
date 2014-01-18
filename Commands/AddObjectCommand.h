#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include <QUndoCommand>
#include "../Model/ResourceManager.h"
#include "../Model/ObjectInstance.h"

class AddObjectCommand : public QUndoCommand
{
public:
    AddObjectCommand(ResourceManager *RM, int newProtoID, int newX, int newY);
    ~AddObjectCommand();

    void undo();
    void redo();

    ObjectInstance *GetObjectInstance() { return object; }

private:
    int protoID;
    int objID;
    int x, y;
    ObjectInstance *object;

    ResourceManager *resources;
};

#endif // ADDOBJECTCOMMAND_H
