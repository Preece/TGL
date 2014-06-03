#ifndef TILESELECTORSCENE_H
#define TILESELECTORSCENE_H

#include <QGraphicsScene>
#include <QFileDialog>
#include <QGraphicsSceneMouseEvent>
#include <QList>

#include "Model/ResourceController.h"
#include "TileWidgetItem.h"

typedef QList<TileCoord> TileList;
typedef QList<QGraphicsItem*> GraphicsItemList;

class TileSelectorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit TileSelectorScene(QObject *parent = 0);
    ~TileSelectorScene();

    void RegisterResourceController(ResourceController * newRM);
    void RepopulateTileSelector();

    TileList GetSelectedTiles();
    
signals:
    void SelectionChanged(TileList newSelection);

    void SelectNewBrush(int type);
    void RevertToPreviousSingleTileBrush();
    
public slots:

    void PackageAndEmitSelection();
    void SelectNewTile(TileCoord origin);

    void SelectTileset(QWidget *topParent);
    void SetTileImage(Image *image);

    void TraverseTileHistory(bool forward);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    ResourceController *resources;
    QImage *spritesheet;

    QPoint clickSpot;
    
    QList<GraphicsItemList> selectionHistory;
    int selectionIndex;

    bool selectionChangeFromHistory;
};

#endif // TILESELECTORSCENE_H
