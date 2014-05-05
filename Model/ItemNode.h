#ifndef SAVABLE_H
#define SAVABLE_H

#include <QFile>
#include <QRect>
#include <QPoint>
#include <QImage>
#include <QHash>

#include "Exporter.h"

typedef QPair<int, int> TileCoord;

struct Tile
{
    TileCoord pos;
    TileCoord origin;
};

class ItemNode
{
protected:
    static int newID;

    int ID;
    QHash<int, ItemNode*> children;

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
