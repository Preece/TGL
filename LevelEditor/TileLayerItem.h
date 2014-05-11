#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include <QGraphicsScene>

#include "../Model/ResourceManager.h"
#include "../Toolbox/TileWidgetItem.h"

class TileLayerItem : public QGraphicsRectItem
{
public:
    TileLayerItem();
    ~TileLayerItem();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

    void SetLayerID(int newID) { layerID = newID; }
    int GetLayerID() { return layerID; }

    void ModifyTileItem(int x, int y, TileCoord newOrigin);

    void ToggleVisibility(bool visible);

    void DestroyAllItems();

    void SelectTilesInArea(QRect area);

private:
    QHash<TileCoord, TileWidgetItem*> items;

    int layerID;
    ResourceManager *resourceManager;
};

#endif // LAYERGROUP_H
