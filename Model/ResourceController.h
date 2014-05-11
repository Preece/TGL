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
#include "Commands/ModifyTilesCommand.h"

class ResourceController : public QObject
{
    Q_OBJECT

public:
    ResourceController();
    ~ResourceController();

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
    int GetLayerOpacity(int layerID);
    void SetLayerVisibility(int layerID, bool visible);

    void ModifyTile(int x, int y, TileCoord origin);
    void PreviewModifyTile(int x, int y, TileCoord origin);
    void ClearPreview();
    TileCoord GetTileOrigin(int x, int y);

    int GetCurrentLayerWidth();
    int GetCurrentLayerHeight();

    void SelectTilesInArea(QRect area);
    QList<Tile> GetSelectedTiles();
    void ClearSelection();

    void SetLayerSelection(int newLayer) { currentLayerID = newLayer; }

    void EndPaintOperation();

    void DestroyAllResources();

signals:
    void ResourceAdded(int newResourceID);
    void ResourceDeleted(int deadResourceID);

    void LayerAdded(int ID);
    void LayerRemoved(int ID);
    void LayerVisibilityUpdated(int ID, bool visible);

    void TileUpdated(int layerID, int x, int y, TileCoord newOrigin);
    void PreviewTileUpdated(int x, int y, TileCoord newOrigin);
    void LayerSizeUpdated(int newW, int newH);

    void SelectionGeometryUpdated(QRect rect);
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

#endif // ResourceController_H
