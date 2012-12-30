#include "ObjectPrototype.h"

ObjectPrototype::ObjectPrototype()
{
    spriteID = 0;
    objectType = 0;
    behavior = 0;
}

bool ObjectPrototype::Export(Exporter *exporter)
{
    exporter->WriteInt(spriteID);
    exporter->WriteString(name);
    exporter->WriteInt(objectType);
    exporter->WriteInt(behavior);

    exporter->WriteInt(customValues.count());

    QMap<QString, QVariant>::iterator i;
    for (i = customValues.begin(); i != customValues.end(); ++i)
    {
        exporter->WriteString(i.key());
        exporter->WriteVariant(i.value());
    }

    return true;
}

bool ObjectPrototype::Import(Exporter *exporter)
{
    exporter->ReadInt(spriteID);
    exporter->ReadString(name);
    exporter->ReadInt(objectType);
    exporter->ReadInt(behavior);

    int customCount;
    exporter->ReadInt(customCount);

    QMap<QString, QVariant>::iterator i;
    customValues.clear();

    for (int i = 0; i < customCount; i++)
    {
        QString key;
        QVariant value;

        exporter->ReadString(key);
        exporter->ReadVariant(value);

        customValues.insert(key, value);
    }

    return true;
}
