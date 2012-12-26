#ifndef OBJECT_INSTANCE_H
#define OBJECT_INSTANCE_H

#include "ObjectPrototype.h"

#include "Savable.h"

class ObjectInstance : public Savable
{
public:

    ObjectInstance();

    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "OBIN"; }

    void SetPrototypeID(int newProtoID) { prototypeID = newProtoID; }
    void UnattachPrototype();
    int GetPrototypeID();

	bool SetPosition(int newX, int newY);
	int GetX();
	int GetY();

private:
    int prototypeID;

    int x, y;
};

#endif
