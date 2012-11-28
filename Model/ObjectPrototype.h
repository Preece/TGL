#ifndef OBJECT_PROTOTYPE_H
#define OBJECT_PROTOTYPE_H

#include <QString>
#include <QImage>
#include <QMap>
#include <QVariant>

#include "Savable.h"

class ObjectPrototype : public Savable
{
private:
	int spriteID;

    QString name;
    int type;
    int behavior;

    QMap<QString, QVariant> customValues;

public:
    ObjectPrototype();

    bool SaveToFile(QFile &file);
    bool LoadFromFile(QFile &file);

    QString GetObjectName() { return name; }
    void SetObjectName(QString newName) { name = newName; }

    int GetType() { return type; }
    void SetType(int newType) { type = newType; }

    int GetBehavior() { return behavior; }
    void SetBehavior(int newBehavior) { behavior = newBehavior; }

    void AttachSprite(int newSpriteID) { spriteID = newSpriteID; }
    int GetSpriteID() { return spriteID; }
    bool UnattachSprite() { spriteID = 0; }

    void AddCustomValue(QString newName, QVariant newValue) { customValues.insert(newName, newValue); }
    QMap<QString, QVariant> GetCustomValues() { return customValues; }
    void ClearCustomValues() { customValues.clear(); }


};

#endif
