#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QDialog>
#include <QHash>
#include <QStringList>
#include <QUndoStack>

#include "Sprite.h"
#include "Image.h"
#include "TileLayer.h"
#include "LevelProperties.h"

#include "Commands/AddResourceCommand.h"
#include "Commands/DeleteResourceCommand.h"
#include "Commands/ModifyTilesCommand.h"

class ResourceManager : public QObject
{
    Q_OBJECT

public:
    ResourceManager();
    ~ResourceManager();

public slots:
    void Undo();
    void Redo();

    LevelProperties *GetLevelProperties() { return &levelProperties; }

    int AddImage(Image *newImage);
    bool DeleteImage(int ID);
    Image *GetImage(int ID);
    Image *GetImageByIndex(int index);
    int GetImageCount() { return imageMap.count(); }

    QImage *GetTileset();
    QPixmap GetTilePixmap(TileCoord coord);

    void AddTileLayer(TileLayer *newLayer);
    void DeleteTileLayer(int ID);
    TileLayer *GetTileLayer(int ID);
    TileLayer *GetLayerByIndex(int index);
    int GetLayerCount() { return layerMap.count(); }
    int GetLayerOpacity(int layerID);

    void ModifyTile(int layerID, int x, int y, TileCoord origin);
    TileCoord GetTileOrigin(int layerID, int x, int y);
    int GetTileCount(int layerID);
    Tile *GetTileByIndex(int layerID, int i);
    void EndPaintOperation();

    void DestroyAllResources();

signals:
    void LayerListModified(int newID);
    void ImageListModified();

private:
    QHash<int, Image*> imageMap;
    QHash<int, TileLayer*> layerMap;

    LevelProperties levelProperties;

    QUndoStack *undo;
    ModifyTilesCommand *modifyTiles;

    QHash<TileCoord, QPixmap> pixmapCache;
};

#endif // RESOURCEMANAGER_H
