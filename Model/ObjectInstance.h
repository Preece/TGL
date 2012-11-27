#ifndef OBJECT_INSTANCE_H
#define OBJECT_INSTANCE_H

#include "ObjectPrototype.h"

#include "Savable.h"

class ObjectInstance : public Savable
{
private:
    int prototypeID;
	int ID;

	int x, y;

public:
    bool SaveToFile(QFile &file);
    bool LoadFromFile(QFile &file);

    bool AttachPrototype(int newProtoID);
	bool UnattachPrototype();
    int GetPrototypeID();

	bool SetPosition(int newX, int newY);
	int GetX();
	int GetY();
};

#endif
