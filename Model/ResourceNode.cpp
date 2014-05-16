#include "ResourceNode.h"

int ResourceNode::newID = 1;

ResourceNode::ResourceNode()
{
    //when the resource is created, automatically generate an ID
    ID = GenerateID();
    type = UnknownType;
}

ResourceNode::~ResourceNode()
{
}

int ResourceNode::GenerateID()
{
    return newID++;
}

void ResourceNode::RegisterID(int registeredID)
{
    //loop and increase the newID value until it is bigger than the
    //ID being registered
    while(registeredID >= newID)
        newID++;
}

void ResourceNode::AddProperty(QString name, QVariant value)
{
    properties[name] = value;

    for(int i = 0; i < children.count(); i++)
        children[i].AddProperty(name, value);
}

void ResourceNode::RemoveProperty(QString name)
{
    if(properties.contains(name))
    {
        properties.remove(name);

        for(int i = 0; i < children.count(); i++)
            children[i].RemoveProperty(name);
    }
}

QVariant ResourceNode::GetProperty(QString name)
{
    if(properties.contains(name))
        return properties[name];
    else
        return QVariant();
}

void ResourceNode::SetProperty(QString name, QVariant value)
{
    if(properties.contains(name))
        properties[name] = value;
}
