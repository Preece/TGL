#include "ObjectInstanceItem.h"

ObjectInstanceItem::ObjectInstanceItem()
{
}

void ObjectInstanceItem::MoveItem(int x, int y)
{
    setPos(x, y);

    if(object)
        object->SetPosition(x, y);
}
