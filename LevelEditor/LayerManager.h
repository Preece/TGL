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
#include "Brushes/TileBrush.h"

class LayerManager : public QGraphicsScene
{
    Q_OBJECT

public:
    LayerManager();
    ~LayerManager();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }
    void RepopulateLayer(LayerGroup *dirtyLayer);
    void AddLayer(Layer *newLayer);
    void RemoveLayer(Layer *dirtyLayer);

    void EyedropTile(QPoint pos);

    void AddObjectItem(QPoint pos, ObjectPrototype *proto);

    bool IsLayerSelected();
    LayerGroup *GetSelectedLayer();
    int GetLayerCount() { return layers.count(); }
    void SetLayerSelection(int newSelection);
    QString GetLayerName(int index);

    void UpdateLayerOpacity(Layer *opaqueLayer);

    void ToggleLayerVisibility(int layerIndex, bool show);

    int GetSelectedTileID();

public slots:
    void SetSelectedTile(TileItem *newTile) { currentTile = newTile; }

    void ToggleGrid(bool show = true);

    void SetBrush(TileBrush *newBrush);

signals:
    void SelectNewTile(int ID);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<LayerGroup*> layers;
    LayerGroup *currentLayer;

    ResourceManager *resourceManager;
    TileItem *currentTile;

    QGraphicsItemGroup *grid;

    TileBrush *currentBrush;
    QPoint lastPaintSpot;
    QPoint lastPreviewSpot;
};

#endif // LAYERMANAGER_H
