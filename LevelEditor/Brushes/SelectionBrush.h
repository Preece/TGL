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

    virtual void Press(int x, int y, ResourceManager *resources);
    virtual void Move(int x, int y, ResourceManager *resources, bool leftButtonDown);
    virtual void Release(int, int, ResourceManager *resources);
    virtual void Deselect(ResourceManager *resources);

    QString GetType() { return "selector"; }
    QCursor GetCursor() { return QCursor(Qt::CrossCursor); }

    void PopOutSelectedTiles(ResourceManager *resources);
    void IntegrateDraggingTiles(ResourceManager *resources);

    QList<Tile> GetDraggingTiles() { return draggingTiles; }
    void SetDraggingTiles(ResourceManager *resources, QList<Tile> newTiles);
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
