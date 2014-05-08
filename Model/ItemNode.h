#ifndef SAVABLE_H
#define SAVABLE_H

#include <QFile>
#include <QRect>
#include <QPoint>
#include <QImage>
#include <QHash>

#include "ObjectProperty.h"

typedef QHash<QString,ObjectProperty> PropertyList;
typedef QPair<int, int> TileCoord;

struct Tile
{
    TileCoord pos;
    TileCoord origin;
};

class ObjectNode
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
    ObjectNode();
    virtual ~ObjectNode();

    int GetID() { return ID; }

    //copies into a new child and returns the object
    virtual ObjectNode CreateChild(ObjectNode *parent) {};

    void AddProperty(QString name, QVariant value, bool inherent = false);
    void RemoveProperty(QString name);

    QVariant GetPropertyValue(QString name);
    ObjectProperty GetProperty(QString name);
    PropertyList GetAllProperties() { return properties; }

    QList<ObjectNode> GetChildren() { return children; }

private:
    ObjectNode *parent;
    PropertyList properties;
    QList<ObjectNode> children;

};

#endif // SAVABLE_H
