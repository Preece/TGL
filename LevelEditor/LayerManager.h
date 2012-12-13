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
    Q_OBJECT

public:
    LayerManager();
    ~LayerManager();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }
    void RepopulateLayer(LayerGroup *dirtyLayer);
    void AddLayer(QString name);

    void ModifyTile(QPoint pos, int ID);
    void ModifyTile(int tileX, int tileY, int ID, bool repopulate = true);
    void FloodFill(int tileX, int tileY, int newTileID, int oldTileID);
    void EraseTile(QPoint pos);
    void EyedropTile(QPoint pos);
    void AddTileItem(int x, int y, int ID);

    void AddObjectItem(QPoint pos, ObjectPrototype *proto);

    bool IsLayerSelected();
    LayerGroup *GetSelectedLayer();
    int GetLayerCount() { return layers.count(); }
    void SetLayerSelection(int newSelection);
    QString GetLayerName(int index);

    void ToggleLayerVisibility(int layerIndex, bool show);

public slots:
    void SetSelectedTile(TileItem *newTile) { currentTile = newTile; }

    void ToggleGrid(bool show = true);

    void SetTool(int newTool) { selectedTool = newTool; }

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

    int selectedTool;
};

#endif // LAYERMANAGER_H
