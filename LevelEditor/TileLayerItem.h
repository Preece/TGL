#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include <QGraphicsScene>

#include "../Model/ResourceController.h"
#include "../Toolbox/TileWidgetItem.h"

class TileLayerItem : public QGraphicsRectItem
{
public:
    TileLayerItem();
    ~TileLayerItem();

    void RegisterResourceManager(ResourceController *newRM) { resourceController = newRM; }

    void SetLayerID(int newID) { layerID = newID; }
    int GetLayerID() { return layerID; }

    void ModifyTileItem(int x, int y, TileCoord newOrigin);

    void ToggleVisibility(bool visible);

    void DestroyAllItems();

    void SelectTilesInArea(QRect area);

private:
    QHash<TileCoord, TileWidgetItem*> items;

    int layerID;
    ResourceController *resourceController;
};

#endif // LAYERGROUP_H
