#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QDialog>
#include <QList>
#include <QStringList>

#include "Sprite.h"
#include "ObjectInstance.h"
#include "ObjectPrototype.h"
#include "Image.h"

class ResourceManager : public QObject
{
    Q_OBJECT

    //ResourceManager(QObject *parent = 0);

private:
    QList<Sprite*> spriteList;
    QList<ObjectPrototype*> objectPrototypeList;
    QList<ObjectInstance*> objectInstanceList;
    QList<Image*> imageList;


public:
    ResourceManager();

public slots:
    int AddSprite(Sprite *newSprite);
    bool DeleteSprite(int ID);
    Sprite *GetSprite(int ID);
    Sprite *GetSpriteByIndex(int index);
    int GetSpriteCount() { return spriteList.count(); }

    int AddObjectPrototype(ObjectPrototype *newObjectPrototype);
    bool DeleteObjectPrototype(int ID);
    ObjectPrototype *GetObjectPrototype(int ID);

    int AddObjectInstance(ObjectInstance *newObjectInstance);
    bool DeleteObjectInstance(int ID);
    ObjectInstance *GetObjectInstance(int ID);

    int AddImage(Image *newImage);
    bool DeleteImage(int ID);
    Image *GetImage(int ID);
    Image *GetImageByIndex(int index);
    int GetImageCount() { return imageList.count(); }

    void DestroyAllResources();

signals:
    void SpriteListModified(QStringList spriteNameList);

    void ObjectPrototypeListModified(QStringList objectPrototypeNameList, int type);

    //void ObjectInstanceAdded(QImage symbol, int ID);

};

#endif // RESOURCEMANAGER_H
