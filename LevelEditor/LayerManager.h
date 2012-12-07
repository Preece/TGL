#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QVariant>
#include <QAbstractListModel>
#include <QItemSelectionModel>

#include "LevelLayer.h"

class LayerManager : public QGraphicsScene
{
public:
    LayerManager();
    ~LayerManager();

    void AddObjectItem(QPoint pos, ObjectPrototype *proto);
    void ModifyTile(int tileX, int tileY, TileItem *newTile);
    void ModifyTile(QPoint pos);

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

    void AddLayer(QString name);

    bool IsLayerSelected();
    LevelLayer *GetSelectedLayer();
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
    QList<LevelLayer*> layers;
    LevelLayer *currentSelection;

    ResourceManager *resourceManager;
    TileItem *currentTile;

    QGraphicsItemGroup *grid;

    int selectedTool;
};

#endif // LAYERMANAGER_H
