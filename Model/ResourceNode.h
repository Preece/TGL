#ifndef SAVABLE_H
#define SAVABLE_H

#include <QFile>
#include <QRect>
#include <QPoint>
#include <QImage>
#include <QHash>
#include <QVariant>

typedef QPair<int, int> TileCoord;
typedef QHash<QString, QVariant> PropertyList;

struct Tile
{
    TileCoord pos;
    TileCoord origin;
};

class ResourceNode
{
protected:
    static int newID;
    int ID;

    int GenerateID();

    //this is used when loading a file. It will make sure the new
    //ID's generated don't conflict with existing ones. All loaded
    //objects should register their ID's.
    void RegisterID(int registeredID);

public:
    ResourceNode();
    virtual ~ResourceNode();

    int GetID() { return ID; }

    void AddProperty(QString name, QVariant value);
    void RemoveProperty(QString name);

    QVariant GetProperty(QString name);
    void SetProperty(QString name, QVariant value);
    QHash<QString, QVariant> GetAllProperties() { return properties; }

    QList<ResourceNode> GetChildren() { return children; }

private:
    ResourceNode *parent;
    PropertyList properties;
    QList<ResourceNode> children;

};

#endif // SAVABLE_H
