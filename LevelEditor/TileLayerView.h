#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include <QGraphicsScene>

#include "../Model/TileLayer.h"
#include "../Model/ResourceManager.h"
#include "../Toolbox/TileWidgetItem.h"

struct TileData
{
    TileCoord pos;
    TileCoord origin;
};

class TileLayerView : public QGraphicsRectItem
{
public:
    TileLayerView();
    ~TileLayerView();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

    void SetLayerID(int newID) { layerID = newID; }
    int GetLayerID() { return layerID; }

    void ModifyTile(int x, int y, TileCoord newOrigin);
    void PreviewModifyTile(int x, int y, TileCoord newOrigin);
    void ClearPreview();

    TileCoord GetTileOrigin(int x, int y);
    void SetLayerSize(int w, int h);

    void ToggleVisibility(bool visible);

    int GetLayerWidth() { return widthInTiles; }
    int GetLayerHeight() { return heightInTiles; }

    void DestroyAllItems();
    void RepopulateTiles();

    void SelectTilesInArea(QRect area);
    QList<TileData> GetSelectedItems();
    void SelectPreviewItems();
    bool SelectedTileAtPos(int x, int y);

private:
    void ModifyTileWidgetItem(int x, int y, TileCoord newOrigin);

    int widthInTiles, heightInTiles;

    QHash<TileCoord, TileWidgetItem*> items;

    QList<TileWidgetItem*> previewItems;

    int layerID;
    ResourceManager *resourceManager;
};

#endif // LAYERGROUP_H
