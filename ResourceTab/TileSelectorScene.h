#ifndef TILESELECTORSCENE_H
#define TILESELECTORSCENE_H

#include <QGraphicsScene>
#include "Model/ResourceManager.h"
#include "TileWidgetItem.h"

class TileSelectorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit TileSelectorScene(QObject *parent = 0);

    void RegisterResourceManager(ResourceManager * newRM) { resources = newRM; }
    
    bool IsTileSelected() { if(selectedItems().count() > 0) return true; return false; }
    
    TileWidgetItem *GetSelectedTile() { if(IsTileSelected()) return dynamic_cast<TileWidgetItem*>(selectedItems()[0]); return NULL; }
signals:
    
public slots:

    void SelectNewTile(TileCoord origin);

private:
    ResourceManager *resources;
    
};

#endif // TILESELECTORSCENE_H
