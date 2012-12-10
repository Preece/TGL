#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QVariant>
#include <QAbstractListModel>
#include <QItemSelectionModel>

#include "../Model/Layer.h"
#include "../Model/ObjectPrototype.h"
#include "../Model/ResourceManager.h"
#include "LayerGroup.h"
#include "TileItem.h"

class LayerManager : public QGraphicsScene
{
public:
    LayerManager();
    ~LayerManager();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }
    void RepopulateLayer(LayerGroup *dirtyLayer);
    void AddLayer(QString name);

    void ModifyTile(QPoint pos);
    void FloodFill(QPoint pos);
    void AddObjectItem(QPoint pos, ObjectPrototype *proto);

    bool IsLayerSelected();
    LayerGroup *GetSelectedLayer();
    int GetLayerCount() { return layers.count(); }
    void SetLayerSelection(int newSelection);
    QString GetLayerName(int index);

    void ToggleLayerVisibility(int layerIndex, bool show);

    void SetTool(int newTool) { selectedTool = newTool; }

public slots:
    void SetSelectedTile(TileItem *newTile) { currentTile = newTile; }

    void ToggleGrid(bool show = true);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<LayerGroup*> layers;
    LayerGroup *currentLayer;

    ResourceManager *resourceManager;
    TileItem *currentTile;

    QGraphicsItemGroup *grid;

    int selectedTool;
};

#endif // LAYERMANAGER_H
