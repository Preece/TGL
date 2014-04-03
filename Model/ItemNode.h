#ifndef SAVABLE_H
#define SAVABLE_H

#include "Exporter.h"

#include <QFile>
#include <QRect>
#include <QPoint>
#include <QImage>
#include <QList>
#include <QMap>

class ItemNode
{
protected:
    static int newID;

    int ID;
    QMap<int, ItemNode*> children;

    int GenerateID();

    //this is used when loading a file. It will make sure the new
    //ID's generated don't conflict with existing ones. All loaded
    //objects should register their ID's.
    void RegisterID(int registeredID);

public:
    ItemNode();
    virtual ~ItemNode();

    int GetID() { return ID; }

    virtual QString GetType() = 0;

    void AddChild(ItemNode *newChild);
    ItemNode *GetChild(int ID);
    ItemNode *GetChildByIndex(int i);
    int GetChildCount();
    void RemoveChild(int ID);


};

#endif // SAVABLE_H
