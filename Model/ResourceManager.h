#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QDialog>
#include <QList>
#include <QStringList>

#include "Sprite.h"
#include "ObjectInstance.h"
#include "ObjectPrototype.h"
#include "Image.h"
#include "Tile.h"
#include "Layer.h"
#include "Model/LevelProperties.h"

class ResourceManager : public QObject
{
    Q_OBJECT

    //ResourceManager(QObject *parent = 0);
public:
    ResourceManager();

public slots:

    LevelProperties *GetLevelProperties() { return &levelProperties; }

    int AddSprite(Sprite *newSprite);
    bool DeleteSprite(int ID);
    Sprite *GetSprite(int ID);
    Sprite *GetSpriteByIndex(int index);
    int GetSpriteCount() { return spriteList.count(); }

    int AddObjectPrototype(ObjectPrototype *newObjectPrototype);
    bool DeleteObjectPrototype(int ID);
    ObjectPrototype *GetObjectPrototype(int ID);
    ObjectPrototype *GetObjectPrototypeByIndex(int index);
    int GetObjectPrototypeCount() { return objectPrototypeList.count(); }

    int AddObjectInstance(ObjectInstance *newObjectInstance);
    bool DeleteObjectInstance(int ID);
    ObjectInstance *GetObjectInstance(int ID);

    int AddImage(Image *newImage);
    bool DeleteImage(int ID);
    Image *GetImage(int ID);
    Image *GetImageByIndex(int index);
    int GetImageCount() { return imageList.count(); }

    QPixmap GetSpriteSymbol(int spriteID);
    QImage *GetTileset();

    void AddTile(Tile *newTile);
    void ClearTiles();
    int GetTileCount() { return tileList.count(); }
    Tile *GetTile(int ID);
    Tile *GetTile(int x, int y);

    void AddLayer(Layer *newLayer);
    void DeleteLayer(int ID);
    Layer *GetLayer(int ID);
    Layer *GetLayerByIndex(int index);
    int GetLayerCount() { return layerList.count(); }

    void DestroyAllResources();

signals:
    void SpriteListModified(QStringList spriteNameList);

    void ObjectPrototypeListModified(QStringList objectPrototypeNameList, int type);

    //void ObjectInstanceAdded(QImage symbol, int ID);

private:
    QList<Sprite*> spriteList;
    QList<ObjectPrototype*> objectPrototypeList;
    QList<ObjectInstance*> objectInstanceList;
    QList<Image*> imageList;
    QList<Tile*> tileList;
    QList<Layer*> layerList;

    LevelProperties levelProperties;
};

#endif // RESOURCEMANAGER_H
