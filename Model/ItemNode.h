#ifndef SAVABLE_H
#define SAVABLE_H

#include "Exporter.h"

#include <QFile>
#include <QRect>
#include <QPoint>
#include <QImage>
#include <QHash>

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
    virtual bool Export(Exporter *exporter) = 0;
    virtual bool Import(Exporter *exporter) = 0;

    void Save(Exporter *exporter);
    void Load(Exporter *exporter);

    void AddChild(ItemNode *newChild);
    ItemNode *GetChild(int ID);
    ItemNode *GetChildByIndex(int i);
    int GetChildCount();
    void RemoveChild(int ID);


};

#endif // SAVABLE_H
