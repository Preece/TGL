#ifndef OBJECTSELECTORITEM_H
#define OBJECTSELECTORITEM_H

#include <QListWidgetItem>

#include "Model/ObjectPrototype.h"

class ObjectSelectorItem : public QListWidgetItem
{
private:
    ObjectPrototype *object;

public:
    ObjectSelectorItem();

    void SetObject(ObjectPrototype *newObject) { object = newObject; }
    ObjectPrototype *GetObject() { return object; }
};

#endif // OBJECTSELECTORITEM_H
