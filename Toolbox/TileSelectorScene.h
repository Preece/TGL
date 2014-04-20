#ifndef TILESELECTORSCENE_H
#define TILESELECTORSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>

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
    void RepopulateTileSelector();
    
signals:
    void SelectionChanged(TileList newSelection);

    void SelectNewBrush(int type);
    
public slots:

    void PackageAndEmitSelection();
    void SelectNewTile(TileCoord origin);

    void SelectTileset();

    void TraverseTileHistory(bool forward);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    TileList GetSelectedTiles();

    ResourceManager *resources;
    QImage *spritesheet;

    QRubberBand *selection;
    QPoint clickSpot;
    
    QList<QGraphicsItem*> selectionHistory;
    int selectionIndex;

    bool selectionChangeFromHistory;
};

#endif // TILESELECTORSCENE_H
