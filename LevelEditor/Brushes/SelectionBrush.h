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

    virtual void Press(int x, int y, TileController *tiles);
    virtual void Move(int x, int y, TileController *tiles, bool leftButtonDown);
    virtual void Release(int, int, TileController *tiles);
    virtual void Deselect(TileController *tiles);

    QString GetType() { return "selector"; }
    QCursor GetCursor() { return QCursor(Qt::CrossCursor); }

    void PopOutSelectedTiles(TileController *tiles);
    void IntegrateDraggingTiles(TileController *tiles);

    QList<Tile> GetDraggingTiles() { return draggingTiles; }
    void SetDraggingTiles(TileController *tiles, QList<Tile> newTiles);
    void ClearDraggingTiles();

private:
    bool DraggingTileAtPos(int x, int y);
	
    QPoint clickSpot;
    QPoint previousMouseSpot;

   	bool dragMode;
    bool clickAfterDrag;

    QList<Tile> draggingTiles;
};

#endif // SELECTIONBRUSH_H
