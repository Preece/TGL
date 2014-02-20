#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include "../Model/TileLayer.h"
#include "../Model/ResourceManager.h"
#include "../ResourceTab/TileWidgetItem.h"

class TileLayerView : public QGraphicsRectItem
{
public:
    TileLayerView();
    ~TileLayerView();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

    void SetLayer(TileLayer *newLayer) { layer = newLayer; }
    TileLayer *GetLayer() { return layer; }

    void AddTileWidgetItem(Tile *newTile);
    void ModifyTile(int x, int y, TileCoord newOrigin);
    void PreviewModifyTile(int x, int y, TileCoord newOrigin);
    void ClearPreview();
    Tile *GetTile(int x, int y);

    TileWidgetItem *GetTileWidgetItem(int x, int y);

    TileCoord GetTileOrigin(int x, int y);
    void SetLayerSize(int w, int h);

    void ToggleVisibility(bool visible);

    int GetLayerWidth() { return width; }
    int GetLayerHeight() { return height; }

    void DestroyAllItems();

    void RepopulateTiles();
    void RepopulateObjects();


private:
    QList<TileWidgetItem*> items;
    int width, height;

    QList<TileWidgetItem*> previewItems;

    TileLayer *layer;
    ResourceManager *resourceManager;
};

#endif // LAYERGROUP_H
