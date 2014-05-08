#ifndef OBJECTNODE_H
#define OBJECTNODE_H

#include <QHash>

#include "ObjectProperty.h"

typedef QHash<QString,ObjectProperty> PropertyList;
typedef QList<ObjectNode> ObjectList;

class ObjectNode
{
public:
    ObjectNode();

    //copies into a new child and returns the object
    ObjectNode CreateChild();

    void AddProperty(QString name, QVariant value, bool inherent = false);
    void RemoveProperty(QString name);

private:
    PropertyList properties;

    ObjectList children;
};

#endif // OBJECTNODE_H
