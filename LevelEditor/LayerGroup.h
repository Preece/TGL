#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include <QGraphicsItemGroup>

#include "TileInstanceItem.h"
#include "../Model/Layer.h"
#include "../Model/ResourceManager.h"

class LayerGroup : public QGraphicsItemGroup
{
private:
    QList<TileInstanceItem*> items;

    int layerID;

    ResourceManager *resourceManager;

public:
    LayerGroup();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

    void AddTileInstanceItem(TileInstanceItem* newItem);
    void DeleteAllTileInstanceItems();

    void SetLayerID(int newID) { layerID = newID; }
    int GetLayerID() { return layerID; }

};

#endif // LAYERGROUP_H
