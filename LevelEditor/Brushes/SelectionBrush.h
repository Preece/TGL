#ifndef SELECTIONBRUSH_H
#define SELECTIONBRUSH_H

#include <QList>
#include <QPoint>
#include <QRubberBand>
#include <QGraphicsScene>

#include "TileBrush.h"

class SelectionBrush : public TileBrush
{
public:
    SelectionBrush();
    ~SelectionBrush();

    virtual void Press(int x, int y, TileLayerView *layer);
    virtual void Move(int x, int y, TileLayerView *layer, bool leftButtonDown);
    virtual void Release(int x, int y, TileLayerView *layer);
    virtual void Deselect(TileLayerView *layer);

    QString GetType() { return "selector"; }
    QCursor GetCursor() { return QCursor(Qt::CrossCursor); }

    void IntegrateSelectedTiles(TileLayerView *layer);

    QList<Tile> GetSelectedTiles() { return selectedItems; }
    void SetSelectedTiles(QList<Tile> newTiles) { selectedItems = newTiles; }
    void ClearSelectedTiles();

private:
	bool SelectedTileAtPos(int x, int y);
	
    QPoint clickSpot;
    QPoint previousMouseSpot;

   	bool dragMode;
    bool clickAfterDrag;

    QList<Tile> selectedItems;
};

#endif // SELECTIONBRUSH_H
