#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QVariant>
#include <QAbstractListModel>
#include <QItemSelectionModel>
#include <QRubberBand>
#include <QKeyEvent>

#include "../Model/ResourceManager.h"
#include "TileLayerView.h"
#include "../Toolbox/TileWidgetItem.h"
#include "Brushes/BrushManager.h"

typedef QList<TileCoord> TileList;

class LayerManager : public QGraphicsScene
{
    Q_OBJECT

public:
    LayerManager();
    ~LayerManager();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }
    void RegisterBrushManager(BrushManager *newBM) { brushManager = newBM; }
    
    void AddLayer(int newLayerID);
    void RemoveLayer(int dirtyLayerID);
    void UpdateLayerOpacity(int opaqueLayerID);
    void ClearPreview();

    void CatastrophicRepopulation();

signals:
    void SelectNewTile(TileCoord ID);
    void SelectNewBrush(int brushID);

public slots:
    void ToggleLayerVisibility(int layerIndex, bool show);
    void ToggleGrid(bool show = true);
    void ToggleSelectionMode(bool selection);

    void SetLayerSelection(int newSelection);

    void RefreshPreview();
    void SelectPreviewItems();

    void UpdateTile(int layerID, int x, int y, TileCoord newOrigin);
    void UpdatePreviewTile(int x,int y, TileCoord origin);

    void UpdateSelectionGeometry(QRect rect);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void EyedropTile(QPoint pos);

    QList<TileLayerView*> layers;
    TileLayerView *currentLayer;

    QHash<TileCoord, TileWidgetItem*> previewItems;

    ResourceManager *resourceManager;
    BrushManager *brushManager;

    QGraphicsItemGroup *grid;

    QPoint lastPreviewSpot;
};

#endif // LAYERMANAGER_H
