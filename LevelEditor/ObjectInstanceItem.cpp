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

/*QVariant ObjectInstanceItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == ItemPositionChange)
    {
        QPoint position = value.toPointF().toPoint();

        if(object)
        {
            object->SetPosition(position.x(), position.y());
        }
    }
}*/
