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

    virtual void Press(int x, int y, ResourceController *resources);
    virtual void Move(int x, int y, ResourceController *resources, bool leftButtonDown);
    virtual void Release(int, int, ResourceController *resources);
    virtual void Deselect(ResourceController *resources);

    QString GetType() { return "selector"; }
    QCursor GetCursor() { return QCursor(Qt::CrossCursor); }

    void PopOutSelectedTiles(ResourceController *resources);
    void IntegrateDraggingTiles(ResourceController *resources);

    QList<Tile> GetDraggingTiles() { return draggingTiles; }
    void SetDraggingTiles(ResourceController *resources, QList<Tile> newTiles);
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
