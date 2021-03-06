#ifndef ResourceController_H
#define ResourceController_H

#include <QHash>
#include <QUndoStack>
#include <QPixmap>

#include "Image.h"
#include "TileLayer.h"
#include "LevelProperties.h"
#include "Clipboard.h"

#include "Commands/AddResourceCommand.h"
#include "Commands/DeleteResourceCommand.h"

class ResourceController : public QObject
{
    Q_OBJECT

public:
    ResourceController();
    ~ResourceController();

    void AddUndoCommand(QUndoCommand* newUndo) { undo->push(newUndo); }

    void PurgeUndoStack();

public slots:
    void Undo();
    void Redo();
    Clipboard *GetClipboard() { return clipboard; }

    ResourceNode *GetResource(int ID);

    LevelProperties *GetLevelProperties() { return &levelProperties; }
    int GetTileWidth();
    int GetTileHeight();

    int AddImage(Image *newImage = NULL);
    bool DeleteImage(int ID);
    Image *GetImage(int imageID);
    QList<Image*> GetAllImages();

    QImage *GetTileset();
    QPixmap GetTilePixmap(TileCoord coord);

    TileLayer *AddTileLayer(TileLayer *layer = NULL);
    void DeleteTileLayer(int ID);
    TileLayer *GetTileLayer(int ID);
    QList<TileLayer*> GetAllLayers();

    void DestroyAllResources();

signals:
    void ResourceAdded(int newResourceID);
    void ResourceDeleted(int deadResourceID);

    void LayerAdded(int ID);
    void LayerRemoved(int ID);

    void SetTilesetImage(Image *image);


private:
    QHash<int, Image*> images;
    QHash<int, TileLayer*> layers;

    LevelProperties levelProperties;

    QUndoStack *undo;

    QHash<TileCoord, QPixmap> pixmapCache;

    Clipboard *clipboard;
};

#endif // ResourceController_H
