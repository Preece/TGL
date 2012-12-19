#ifndef BRUSHPROPERTIESWINDOW_H
#define BRUSHPROPERTIESWINDOW_H

#include <QDialog>
#include <QGraphicsScene>

#include "../../Model/ResourceManager.h"

#include "ScatterBrush.h"
#include "../TileItem.h"

namespace Ui {
class BrushPropertiesWindow;
}

class BrushPropertiesWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit BrushPropertiesWindow(QWidget *parent = 0);
    ~BrushPropertiesWindow();

    void RegisterTileSelector(QGraphicsScene *selector);
    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

    void NewScatterBrush(ScatterBrush *newBrush);
    void EditScatterBrush(ScatterBrush *editBrush);

    bool IsTileSelected();
    int GetSelectedTileID();
    TileItem *GetSelectedTile();
    TileItem *GetTileFromID(int ID);

    void RepopulateTileList();
    
private slots:
    void on_addTile_clicked();

    void on_brushNameInput_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::BrushPropertiesWindow *ui;

    ResourceManager *resourceManager;

    QGraphicsScene tileList;
    QGraphicsScene *tileSelector;

    ScatterBrush *currentScatterBrush;
};

#endif // BRUSHPROPERTIESWINDOW_H
