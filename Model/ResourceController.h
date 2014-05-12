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

public slots:
    void Undo();
    void Redo();
    Clipboard *GetClipboard() { return clipboard; }

    ResourceNode *GetObject(int ID);

    LevelProperties *GetLevelProperties() { return &levelProperties; }
    int GetTileWidth();
    int GetTileHeight();

    int AddImage(Image *newImage);
    bool DeleteImage(int ID);
    Image *GetImage(int imageID);

    QImage *GetTileset();
    QPixmap GetTilePixmap(TileCoord coord);

    void AddTileLayer(TileLayer *newLayer);
    void DeleteTileLayer(int ID);
    TileLayer *GetTileLayer(int ID);

    void DestroyAllResources();

signals:
    void ResourceAdded(int newResourceID);
    void ResourceDeleted(int deadResourceID);

    void LayerAdded(int ID);
    void LayerRemoved(int ID);


private:
    QHash<int, Image*> imageMap;
    QHash<int, TileLayer*> layerMap;

    TileLayer defaultLayer;

    LevelProperties levelProperties;

    QUndoStack *undo;

    QHash<TileCoord, QPixmap> pixmapCache;

    Clipboard *clipboard;
};

#endif // ResourceController_H
