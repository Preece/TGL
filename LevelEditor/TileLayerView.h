#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include <QGraphicsScene>

#include "../Model/TileLayer.h"
#include "../Model/ResourceManager.h"
#include "../Toolbox/TileWidgetItem.h"

class TileLayerView : public QGraphicsRectItem
{
public:
    TileLayerView();
    ~TileLayerView();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

    void SetLayerID(int newID) { layerID = newID; }
    int GetLayerID() { return layerID; }

    void ClearPreview();
    void ModifyTileWidgetItem(int x, int y, TileCoord newOrigin);

    void SetLayerSize(int w, int h);

    void ToggleVisibility(bool visible);

    void DestroyAllItems();
    void RepopulateTiles();

    void SelectTilesInArea(QRect area);
    QList<Tile> GetSelectedItems();
    void SelectPreviewItems();
    bool SelectedTileAtPos(int x, int y);

private:
    int widthInTiles, heightInTiles;

    QHash<TileCoord, TileWidgetItem*> items;

    QList<TileWidgetItem*> previewItems;

    int layerID;
    ResourceManager *resourceManager;
};

#endif // LAYERGROUP_H
