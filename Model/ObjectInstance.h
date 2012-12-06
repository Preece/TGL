#ifndef OBJECT_INSTANCE_H
#define OBJECT_INSTANCE_H

#include "ObjectPrototype.h"

#include "Savable.h"

class ObjectInstance : public Savable
{
public:
    bool SaveToFile(QFile &file);
    bool LoadFromFile(QFile &file);
    QString GetType() { return "OBIN"; }

    bool AttachPrototype(int newProtoID);
	bool UnattachPrototype();
    int GetPrototypeID();

	bool SetPosition(int newX, int newY);
	int GetX();
	int GetY();

private:
    int prototypeID;
    int ID;

    int x, y;
};

#endif
