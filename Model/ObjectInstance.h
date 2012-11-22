#ifndef OBJECT_INSTANCE_H
#define OBJECT_INSTANCE_H

#include "ObjectPrototype.h"

#include "savable.h"

class ObjectInstance : public Savable
{
private:
	ObjectPrototype *prototype;
	int ID;

	int x, y;

public:
    bool SaveToFile(QFile &file);
    bool LoadFromFile(QFile &file);

    bool AttachPrototype(ObjectPrototype *newPrototype);
	bool UnattachPrototype();
    ObjectPrototype *GetPrototype();

	bool SetPosition(int newX, int newY);
	int GetX();
	int GetY();
};

#endif
