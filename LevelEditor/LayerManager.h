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

typedef QList<TileCoord> TileList;

class LayerManager : public QGraphicsScene
{
    Q_OBJECT

public:
    LayerManager();
    ~LayerManager();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }
    void RepopulateLayer(TileLayerView *dirtyLayer);
    void AddLayer(int newLayerID);
    void RemoveLayer(int dirtyLayerID);

    void EyedropTile(QPoint pos);

    bool IsLayerSelected();
    TileLayerView *GetSelectedLayer();
    int GetLayerCount() { return layers.count(); }

    QString GetLayerName(int index);

    void UpdateLayerOpacity(int opaqueLayerID);

    void ToggleLayerVisibility(int layerIndex, bool show);

public slots:
    void RepopulateAllLayers();

    void ToggleGrid(bool show = true);

    void SetBrush(TileBrush *newBrush);

    void SetLayerSelection(int newSelection);

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

    QGraphicsItemGroup *grid;

    TileBrush *currentBrush;

    QPoint lastPreviewSpot;
};

#endif // LAYERMANAGER_H
