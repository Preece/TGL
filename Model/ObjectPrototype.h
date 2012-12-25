#ifndef OBJECT_PROTOTYPE_H
#define OBJECT_PROTOTYPE_H

#include <QString>
#include <QImage>
#include <QMap>
#include <QVariant>

#include "Savable.h"

class ObjectPrototype : public Savable
{
public:
    bool SaveToFile(Exporter *exporter);
    bool LoadFromFile(Exporter *exporter);
    QString GetType() { return "OBPT"; }

    ObjectPrototype();

    QString GetObjectName() { return name; }
    void SetObjectName(QString newName) { name = newName; }

    int GetObjectType() { return objectType; }
    void SetObjectType(int newType) { objectType = newType; }

    int GetBehavior() { return behavior; }
    void SetBehavior(int newBehavior) { behavior = newBehavior; }

    void AttachSprite(int newSpriteID) { spriteID = newSpriteID; }
    int GetSpriteID() { return spriteID; }
    void UnattachSprite() { spriteID = 0; }

    void AddCustomValue(QString newName, QVariant newValue) { customValues.insert(newName, newValue); }
    QMap<QString, QVariant> GetCustomValues() { return customValues; }
    void ClearCustomValues() { customValues.clear(); }

private:
    int spriteID;

    QString name;
    int objectType;
    int behavior;

    QMap<QString, QVariant> customValues;
};

#endif
