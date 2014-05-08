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

void ObjectNode::AddProperty(QString name, QVariant value, bool inherent)
{
    ObjectProperty newProp;
    newProp.SetName(name);
    newProp.SetValue(value);
    newProp.SetInherent(inherent);

    properties[name] = newProp;

    for(int i = 0; i < children.count(); i++)
        children[i].AddProperty(name, value, inherent);
}

void ObjectNode::RemoveProperty(QString name)
{
    if(properties.contains(name))
    {
        if(!properties[name].IsInherent())
        {
            properties.remove(name);

            for(int i = 0; i < children.count(); i++)
                children[i].RemoveProperty(name);
        }
    }
}

ObjectProperty ObjectNode::GetProperty(QString name)
{
    if(properties.contains(name))
        return properties[name];
    else
        return ObjectProperty();
}
