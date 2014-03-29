#include "ItemNode.h"

int ItemNode::newID = 1;

ItemNode::ItemNode()
{
    //when the object is created, automatically generate an ID
    ID = GenerateID();
}

ItemNode::~ItemNode()
{
}

void ItemNode::Save(Exporter *exporter)
{
    exporter->WriteType(ID, GetType());

    Export(exporter);

    for(int i = 0 ; i < GetChildCount(); i++)
    {
        GetChildByIndex(i)->Save(exporter);
    }
}

void ItemNode::AddChild(ItemNode *newChild)
{
    children.append(newChild);
}

ItemNode *ItemNode::GetChild(int ID)
{
    for(int i = 0; i < children.count(); i++)
    {
        if(ID == children[i]->GetID())
        {
            return children[i];
        }
    }

    return NULL;
}

ItemNode *ItemNode::GetChildByIndex(int i)
{
    if(i < 0 || i >= children.count())
        return NULL;

    return children[i];
}

int ItemNode::GetChildCount()
{
    return children.count();
}

void ItemNode::RemoveChild(int ID)
{
    for(int i = 0; i < children.count(); i++)
    {
        if(ID == children[i]->GetID())
        {
            delete children[i];
            children.removeAt(i);
        }
    }
}

int ItemNode::GenerateID()
{
    return newID++;
}

void ItemNode::RegisterID(int registeredID)
{
    //loop and increase the newID value until it is bigger than the
    //ID being registered
    while(registeredID >= newID)
        newID++;
}
