#include "ObjectProperty.h"

ObjectProperty::ObjectProperty()
{
    inherent = false;
}

ObjectProperty::ObjectProperty(QString newName, QVariant newValue, bool newInh)
{
    name = newName;
    value = newValue;
    inherent = newInh;
}

ObjectProperty::ObjectProperty(bool newInh)
{
    inherent = newInh;
}
