#ifndef SELECTIONGRAPHICSSCENE_H
#define SELECTIONGRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>

class SelectionGraphicsScene : public QGraphicsScene
{
    Q_OBJECT

private:
    QGraphicsRectItem *selectionBox;
    QGraphicsPixmapItem *renderSpot;
    QPoint origin;

    QImage spritesheet;

    int currentTool;

public:
    explicit SelectionGraphicsScene(QObject *parent = 0);
    ~SelectionGraphicsScene();

    void mouseMoveEvent (QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent (QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent (QGraphicsSceneMouseEvent *mouseEvent);

    void UpdateSelectionRect(QRect newRect);
    QRect GetSelectionRect() { return selectionBox->rect().toRect(); }
    void HideSelection() { selectionBox->hide(); }
    void ShowSelection() { selectionBox->show(); }

    void UpdateRenderSpot(QPoint newSpot);
    void HideRenderSpot() { renderSpot->hide(); }
    void ShowRenderSpot() { renderSpot->show(); }

    void SetTool(int newTool) { currentTool = newTool; }
    void SetSpritesheet(QImage newSheet) { spritesheet = newSheet; }

    void AutoSelectFrame(int x, int y);
    
signals:
    void SelectionUpdated(QRect newSelection);
    void RenderSpotUpdated(QPoint newRenderSpot);
    
public slots:
    
};

#endif // SELECTIONGRAPHICSSCENE_H
