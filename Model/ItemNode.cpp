#include "ItemNode.h"

int ObjectNode::newID = 1;

ObjectNode::ObjectNode()
{
    //when the object is created, automatically generate an ID
    ID = GenerateID();
}

ObjectNode::~ObjectNode()
{
}

int ObjectNode::GenerateID()
{
    return newID++;
}

void ObjectNode::RegisterID(int registeredID)
{
    //loop and increase the newID value until it is bigger than the
    //ID being registered
    while(registeredID >= newID)
        newID++;
}
