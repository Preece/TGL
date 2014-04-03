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

void ItemNode::AddChild(ItemNode *newChild)
{
    //if the new child exists
    if(!newChild)
        return;

    //place it in the list
    children[newChild->GetID()] = newChild;
}

ItemNode *ItemNode::GetChild(int ID)
{
    if(children.value(ID))
        return children[ID];

    return NULL;
}

ItemNode *ItemNode::GetChildByIndex(int i)
{
    QList<ItemNode*> childList = children.values();

    if(i < 0 || i >= childList.count())
        return NULL;

    return childList[i];
}

int ItemNode::GetChildCount()
{
    return children.count();
}

void ItemNode::RemoveChild(int ID)
{
    if(children.value(ID))
    {
        delete children[ID];
        children[ID] = NULL;
        children.remove(ID);
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
