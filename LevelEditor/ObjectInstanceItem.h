#ifndef OBJECTINSTANCEITEM_H
#define OBJECTINSTANCEITEM_H

#include <QGraphicsPixmapItem>

#include "../Model/ObjectInstance.h"

class ObjectInstanceItem : public QGraphicsPixmapItem
{
public:
    ObjectInstanceItem();

    void SetObject(ObjectInstance *newObj) { object = newObj; }
    ObjectInstance *GetObject() { return object; }

    void MoveItem(int x, int y);

    //QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    
signals:
    
public slots:

private:
    ObjectInstance *object;
    
};

#endif // OBJECTINSTANCEITEM_H
