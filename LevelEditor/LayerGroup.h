#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include <QGraphicsItemGroup>

#include "TileInstanceItem.h"
#include "../Model/Layer.h"
#include "../Model/ResourceManager.h"

class LayerGroup : public QGraphicsItemGroup
{
public:
    LayerGroup();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

    void SetLayer(Layer *newLayer) { layer = newLayer; }
    Layer *GetLayer() { return layer; }

    void ModifyTile(int x, int y, int newType);
    void SetLayerSize(int w, int h);

private:
    QList<TileInstanceItem*> items;
    int width, height;

    Layer *layer;
    ResourceManager *resourceManager;
};

#endif // LAYERGROUP_H
