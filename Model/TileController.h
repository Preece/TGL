#ifndef TILECONTROLLER_H
#define TILECONTROLLER_H

#include <QObject>

#include "ResourceController.h"
#include "Commands/ModifyTilesCommand.h"

class TileController : public QObject
{
    Q_OBJECT
public:
    explicit TileController(QObject *parent = 0);
    ~TileController();

    int GetTileWidth();
    int GetTileHeight();

    void RegisterResourceController(ResourceController *rc) { resources = rc; }

    int GetLayerOpacity(int layerID);
    QPixmap GetTilePixmap(TileCoord coord);

signals:
    void TileUpdated(int layerID, int x, int y, TileCoord newOrigin);
    void PreviewTileUpdated(int x, int y, TileCoord newOrigin);
    void LayerSizeUpdated(int newW, int newH);

    void SelectionGeometryUpdated(QRect rect);
    void SelectPreviewItems();
    void DrawEraserPreview(int x, int y);
    void ClearEraserPreview();

    void LayerVisibilityUpdated(int ID, bool visible);

public slots:
    void ModifyTile(int x, int y, TileCoord origin);
    void PreviewModifyTile(int x, int y, TileCoord origin);
    void ClearPreview();
    TileCoord GetTileOrigin(int x, int y);

    int GetCurrentLayerWidth();
    int GetCurrentLayerHeight();

    void SetLayerVisibility(bool visible);

    void SelectTilesInArea(QRect area);
    QList<Tile> GetSelectedTiles();
    void ClearSelection();

    void SetLayerSelection(int newLayer);

    void EndPaintOperation();

private:
    ResourceController *resources;
    TileLayer *currentLayer;

    QHash<TileCoord, Tile> previewTiles;
    QRect selectionArea;

    ModifyTilesCommand *modifyTiles;
};

#endif // TILECONTROLLER_H
