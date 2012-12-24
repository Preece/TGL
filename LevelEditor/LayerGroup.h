#ifndef LAYERGROUP_H
#define LAYERGROUP_H

#include <QGraphicsItemGroup>

#include "TileInstanceItem.h"
#include "ObjectInstanceItem.h"

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
    void PreviewModifyTile(int x, int y, int newType);
    void ClearPreview();

    int GetTileType(int x, int y);
    void SetLayerSize(int w, int h);

    void AddObjectItem(ObjectInstanceItem *newObj);
    ObjectInstance *GetObject(int ID);
    void DeleteObject(int ID);

    void ToggleVisibility(bool visible);

    int GetLayerWidth() { return width; }
    int GetLayerHeight() { return height; }

    void DestroyAllItems();

private:
    QList<TileInstanceItem*> items;
    int width, height;

    QList<TileInstanceItem*> previewItems;

    Layer *layer;
    ResourceManager *resourceManager;

    QList<ObjectInstanceItem*> objects;
};

#endif // LAYERGROUP_H
