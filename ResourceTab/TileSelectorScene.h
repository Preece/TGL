#ifndef TILESELECTORSCENE_H
#define TILESELECTORSCENE_H

#include <QGraphicsScene>

class TileSelectorScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit TileSelectorScene(QObject *parent = 0);
    
    bool IsTileSelected() { if(selectedItems().count() > 0) return true; return false; }
    
    TileWidgetItem *GetSelectedTile() { if(IsTileSelected()) return selectedItems()[0]; return NULL; }
signals:
    
public slots:
    
};

#endif // TILESELECTORSCENE_H
