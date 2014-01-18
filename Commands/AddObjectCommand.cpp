#include "AddObjectCommand.h"

AddObjectCommand::AddObjectCommand(ResourceManager *RM, int newProtoID, int newX, int newY)
{
    object = NULL;
    protoID = newProtoID;
    objID = 0;
    x = newX;
    y = newY;

    resources = RM;
}

AddObjectCommand::~AddObjectCommand()
{
    //here, we destroy the resource if it is not a part of the model
    if(resources->GetObjectInstance(objID) != object)
        if(object)
        {
            delete object;
            object = NULL;
        }
}

void AddObjectCommand::undo()
{
    if(!resources)
        return;

    //remove the object from the RM
    resources->DeleteObjectInstance(objID);
}

void AddObjectCommand::redo()
{
    //make sure the RM is valid
    if(!resources)
        return;

    //create and fill out a new object
    object = new ObjectInstance;
    objID = object->GetID();
    object->SetPosition(x, y);
    object->SetPrototypeID(protoID);

    //add it to the resource manager
    resources->AddObjectInstance(object);
}
