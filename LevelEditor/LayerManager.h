#ifndef LAYERMANAGER_H
#define LAYERMANAGER_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "LevelLayer.h"

class LayerManager : public QGraphicsScene
{
private:
    //this should be a list of LevelLayer's
    LevelLayer *scaffold;

    ResourceManager *resourceManager;
    TileItem *currentTile;

public:
    LayerManager();
    ~LayerManager();

    void AddObjectItem(QPoint pos, ObjectPrototype *proto);
    void ModifyTile(int tileX, int tileY, TileItem *newTile);
    void ModifyTile(QPoint pos);

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

public slots:
    void SetSelectedTile(TileItem *newTile) { currentTile = newTile; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // LAYERMANAGER_H
