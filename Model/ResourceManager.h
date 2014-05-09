#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QHash>
#include <QUndoStack>
#include <QPixmap>

#include "Image.h"
#include "TileLayer.h"
#include "LevelProperties.h"
#include "Clipboard.h"

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
    Clipboard *GetClipboard() { return clipboard; }

    ObjectNode *GetObject(int ID);

    LevelProperties *GetLevelProperties() { return &levelProperties; }
    int GetTileWidth();
    int GetTileHeight();
    int GetCurrentLayerWidth();
    int GetCurrentLayerHeight();

    int AddImage(Image *newImage);
    bool DeleteImage(int ID);
    Image *GetImage(int imageID);
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
    void SetLayerSelection(int newLayer) { currentLayerID = newLayer; }

    void ModifyTile(int x, int y, TileCoord origin);
    void PreviewModifyTile(int x, int y, TileCoord origin);
    void ClearPreview();
    TileCoord GetTileOrigin(int x, int y);

    void SelectTilesInArea(QRect area);
    QList<Tile> GetSelectedTiles();
    void ClearSelection();



    void EndPaintOperation();

    void DestroyAllResources();

signals:
    void LayerListModified(int newID);
    void ImageListModified();

    void TileUpdated(int layerID, int x, int y, TileCoord newOrigin);
    void PreviewTileUpdated(int x, int y, TileCoord newOrigin);
    void LayerSizeUpdated(int newW, int newH);

    void UpdateSelectionGeometry(QRect rect);
    void SelectPreviewItems();
    void DrawEraserPreview(int x, int y);
    void ClearEraserPreview();

private:
    QHash<int, Image*> imageMap;
    QHash<int, TileLayer*> layerMap;
    int currentLayerID;
    QHash<TileCoord, Tile> previewTiles;
    QRect selectionArea;

    TileLayer defaultLayer;

    LevelProperties levelProperties;

    QUndoStack *undo;
    ModifyTilesCommand *modifyTiles;

    QHash<TileCoord, QPixmap> pixmapCache;

    Clipboard *clipboard;
};

#endif // RESOURCEMANAGER_H
