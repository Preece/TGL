#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QVariant>
#include <QAbstractListModel>
#include <QItemSelectionModel>
#include <QRubberBand>

#include "../Model/TileLayer.h"
#include "../Model/ResourceManager.h"
#include "TileLayerView.h"
#include "../Toolbox/TileWidgetItem.h"
#include "Brushes/TileBrush.h"

typedef QList<TileCoord> TileList;

class LayerManager : public QGraphicsScene
{
    Q_OBJECT

public:
    LayerManager();
    ~LayerManager();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }
    
    void AddLayer(int newLayerID);
    void RemoveLayer(int dirtyLayerID);
    void UpdateLayerOpacity(int opaqueLayerID);
    void ClearPreview();

signals:
    void SelectNewTile(TileCoord ID);
    void SelectNewBrush(int brushID);

public slots:
    void RepopulateAllLayers();

    void ToggleLayerVisibility(int layerIndex, bool show);
    void ToggleGrid(bool show = true);
    void ToggleSelectionMode(bool selection);

    void SetBrushSelection(TileBrush *newBrush, QCursor newCursor);
    void SetLayerSelection(int newSelection);

    void RefreshPreview();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void EyedropTile(QPoint pos);

    QList<TileLayerView*> layers;
    TileLayerView *currentLayer;

    ResourceManager *resourceManager;

    QGraphicsItemGroup *grid;

    TileBrush *currentBrush;

    QPoint lastPreviewSpot;
};

#endif // LAYERMANAGER_H
