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

    void SetLayerID(int newID) { layerID = newID; }
    int GetLayerID() { return layerID; }

    void AddTileWidgetItem(Tile *newTile);
    void ModifyTile(int x, int y, TileCoord newOrigin);
    void PreviewModifyTile(int x, int y, TileCoord newOrigin);
    void ClearPreview();

    TileCoord GetTileOrigin(int x, int y);
    void SetLayerSize(int w, int h);

    void ToggleVisibility(bool visible);
    bool IsVisible();

    int GetLayerWidth() { return widthInTiles; }
    int GetLayerHeight() { return heightInTiles; }

    void DestroyAllItems();

    void RepopulateTiles();
    void RepopulateObjects();


private:
    int widthInTiles, heightInTiles;

    QMap<TileCoord, TileWidgetItem*> items;

    QList<TileWidgetItem*> previewItems;

    int layerID;
    ResourceManager *resourceManager;
};

#endif // LAYERGROUP_H
