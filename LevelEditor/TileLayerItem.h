#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include <QGraphicsScene>

#include "../Model/TileController.h"
#include "../Toolbox/TileWidgetItem.h"

class TileLayerItem : public QGraphicsRectItem
{
public:
    TileLayerItem();
    ~TileLayerItem();

    void RegisterTileController(TileController *newTC) { tileController = newTC; }

    void SetLayerID(int newID) { layerID = newID; }
    int GetLayerID() { return layerID; }

    void ModifyTileItem(int x, int y, TileCoord newOrigin);

    void ToggleVisibility(bool visible);

    void DestroyAllItems();

    void SelectTilesInArea(QRect area);

private:
    QHash<TileCoord, TileWidgetItem*> items;

    int layerID;
    TileController *tileController;
};

#endif // LAYERGROUP_H
