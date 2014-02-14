#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QDialog>
#include <QList>
#include <QStringList>
#include <QUndoStack>

#include "Sprite.h"
#include "Image.h"
#include "Tile.h"
#include "Layer.h"
#include "Model/LevelProperties.h"

#include "../Commands/AddResourceCommand.h"
#include "../Commands/DeleteResourceCommand.h"
#include "../Commands/AddTilesCommand.h"
#include "../Commands/ModifyTilesCommand.h"

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

    int AddImage(Image *newImage);
    bool DeleteImage(int ID);
    Image *GetImage(int ID);
    Image *GetImageByIndex(int index);
    int GetImageCount() { return imageList.count(); }

    QPixmap GetSpriteSymbol(int spriteID);
    QImage *GetTileset();
    QPixmap GetTilePixmap(int ID);

    void AddTile(Tile *newTile);
    void ClearTiles();
    int GetTileCount() { return tileList.count(); }
    Tile *GetTile(int ID);
    Tile *GetTile(int x, int y);

    TileInstance *AddTileInstance(Layer *layer, int x, int y, int newType);
    void ModifyTileInstance(Layer *layer, int x, int y, int newType, int oldType);
    TileInstance *GetTileInstanceByIndex(Layer *layer, int i);
    int GetTileInstanceCount(Layer *layer);

    void AddLayer(Layer *newLayer);
    void DeleteLayer(int ID);
    Layer *GetLayer(int ID);
    Layer *GetLayerByIndex(int index);
    int GetLayerCount() { return layerList.count(); }

    void DestroyAllResources();

    void Undo();
    void Redo();

    void BeginUndoOperation(QString name) { undo->beginMacro(name); }
    void EndUndoOperation() { undo->endMacro(); }

signals:
    void SpriteListModified(QStringList spriteNameList);

    void ObjectPrototypeListModified(QStringList objectPrototypeNameList, int type);

    //void ObjectInstanceAdded(QImage symbol, int ID);

    void UndoRedoPerformed();

private:
    QList<Sprite*> spriteList;
    QList<Image*> imageList;
    QList<Tile*> tileList;
    QList<Layer*> layerList;

    LevelProperties levelProperties;

    QUndoStack *undo;
};

#endif // RESOURCEMANAGER_H
