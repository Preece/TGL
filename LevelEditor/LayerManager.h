#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QVariant>
#include <QAbstractListModel>
#include <QItemSelectionModel>

#include "../Model/TileLayer.h"
#include "../Model/ResourceManager.h"
#include "TileLayerView.h"
#include "../ResourceTab/TileWidgetItem.h"
#include "Brushes/TileBrush.h"

class LayerManager : public QGraphicsScene
{
    Q_OBJECT

public:
    LayerManager();
    ~LayerManager();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }
    void RepopulateLayer(TileLayerView *dirtyLayer);
    void AddLayer(TileLayer *newLayer);
    void RemoveLayer(TileLayer *dirtyLayer);

    void EyedropTile(QPoint pos);

    bool IsLayerSelected();
    TileLayerView *GetSelectedLayer();
    int GetLayerCount() { return layers.count(); }
    void SetLayerSelection(int newSelection);
    QString GetLayerName(int index);

    void UpdateLayerOpacity(TileLayer *opaqueLayer);

    void ToggleLayerVisibility(int layerIndex, bool show);

    void RepopulateAllLayers();

public slots:
    void SetSelectedTile(TileWidgetItem *newTile) { currentTile = newTile; }

    void ToggleGrid(bool show = true);

    void SetBrush(TileBrush *newBrush);

signals:
    void SelectNewTile(TileCoord ID);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<TileLayerView*> layers;
    TileLayerView *currentLayer;

    ResourceManager *resourceManager;
    TileWidgetItem *currentTile;

    QGraphicsItemGroup *grid;

    TileBrush *currentBrush;

    QPoint lastPreviewSpot;
};

#endif // LAYERMANAGER_H
