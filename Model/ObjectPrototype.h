#ifndef OBJECT_PROTOTYPE_H
#define OBJECT_PROTOTYPE_H

#include <QString>
#include <QImage>

#include "Savable.h"

class ObjectPrototype : public Savable
{
private:
	int spriteID;

public:
    bool SaveToFile(QFile &file);
    bool LoadFromFile(QFile &file);

    QString GetObjectName();
    QImage GetSmallSymbol();
    QImage GetSymbol();

	bool AttachSprite(int newSpriteID);
	bool UnattachSprite();
};

#endif
