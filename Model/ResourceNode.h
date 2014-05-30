#ifndef SAVABLE_H
#define SAVABLE_H

#include <QFile>
#include <QRect>
#include <QPoint>
#include <QImage>
#include <QMap>
#include <QVariant>

typedef QPair<int, int> TileCoord;
typedef QMap<QString, QVariant> PropertyList;

struct Tile
{
    TileCoord pos;
    TileCoord origin;
};

enum ResourceType {
    UnknownType = 0,
    ImageType,
    TilesetType,
    TileLayerType
};

class ResourceNode
{
protected:
    static int newID;
    int ID;
    ResourceType type;

    int GenerateID();
    void RegisterID(int registeredID);

public:

    ResourceNode();
    virtual ~ResourceNode();
    void Load(int startID, ResourceType newType, QMap<QString, QVariant> properties);

    int GetID() { return ID; }

    void SetType(ResourceType newType) { type = newType; }
    ResourceType GetType() { return type; }

    void AddProperty(QString name, QVariant value);
    void RemoveProperty(QString name);

    QVariant GetProperty(QString name);
    void SetProperty(QString name, QVariant value);
    QMap<QString, QVariant> GetAllProperties() { return properties; }

    QList<ResourceNode> GetChildren() { return children; }

private:
    PropertyList properties;
    QList<ResourceNode> children;
};

#endif // SAVABLE_H
