#ifndef TILESELECTORSCENE_H
#define TILESELECTORSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "Model/ResourceManager.h"
#include "../SpriteEditor/SpritesheetSelector.h"
#include "TileWidgetItem.h"

typedef QList<TileCoord> TileList;

class TileSelectorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit TileSelectorScene(QObject *parent = 0);
    ~TileSelectorScene();

    void RegisterResourceManager(ResourceManager * newRM) { resources = newRM; }
    
    bool IsTileSelected() { if(selectedItems().count() > 0) return true; return false; }
    
    TileWidgetItem *GetSelectedTile() { if(IsTileSelected()) return dynamic_cast<TileWidgetItem*>(selectedItems()[0]); return NULL; }
    TileList GetSelectedTiles();

    void RepopulateTileSelector();
    
signals:
    void SelectionChanged(TileList newSelection);

    void SelectEraser();
    
public slots:

    void PackageAndEmitSelection();
    void SelectNewTile(TileCoord origin);

    void SelectTileset();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    ResourceManager *resources;
    QImage *spritesheet;

    QRubberBand *selection;
    QPoint clickSpot;
    
};

#endif // TILESELECTORSCENE_H