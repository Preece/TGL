#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QKeyEvent>
#include <QGraphicsRectItem>

#include "../Model/TileController.h"
#include "TileView.h"
#include "TileLayerItem.h"
#include "../Toolbox/TileWidgetItem.h"
#include "Brushes/BrushManager.h"

typedef QList<TileCoord> TileList;

class TileScene : public QGraphicsScene
{
    Q_OBJECT

public:
    TileScene();
    ~TileScene();

    void RegisterTileController(TileController *newRC);
    void RegisterBrushManager(BrushManager *newBM) { brushManager = newBM; }
    

    void UpdateLayerOpacity(int opaqueLayerID);
    void ClearPreview();

signals:
    void SelectNewTile(TileCoord ID);
    void SelectNewBrush(int brushID);

public slots:
    void AddLayer(int newLayerID);
    void DeleteLayer(int ID);

    void ToggleGrid(bool show = true);
    void ToggleSelectionMode(bool selection);

    void SetLayerSelection(int newSelection);
    void UpdateLayerVisibility(int ID, bool visible);

    void RefreshPreview();
    void SelectPreviewItems();

    void UpdateTile(int layerID, int x, int y, TileCoord newOrigin);
    void UpdatePreviewTile(int x,int y, TileCoord origin);

    void UpdateSelectionGeometry(QRect rect);
    void UpdateSceneSize(int w, int h);

    void DrawEraserPreview(int x, int y);
    void ClearEraserPreview();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    void EyedropTile(QPoint pos);

    QList<TileLayerItem*> layers;
    TileLayerItem *currentLayer;

    QHash<TileCoord, TileWidgetItem*> previewItems;
    QList<QGraphicsRectItem*> eraserPreviewItems;

    TileController *tileController;
    BrushManager *brushManager;

    QGraphicsItemGroup *grid;

    QPoint lastPreviewSpot;
};

#endif // LAYERMANAGER_H
