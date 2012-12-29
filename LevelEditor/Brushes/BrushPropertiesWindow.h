#ifndef BRUSHPROPERTIESWINDOW_H
#define BRUSHPROPERTIESWINDOW_H

#include <QDialog>
#include <QGraphicsScene>

#include "../../Model/ResourceManager.h"

#include "ScatterBrush.h"
#include "SmartBrush.h"

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

    void NewBrush(ComplexBrush *newBrush);
    void EditBrush(ComplexBrush *editBrush);

    void SetListIndex(int newIndex) { currentListIndex = newIndex; }

    void ShowScatterControls();
    void ShowSmartControls();

    bool IsTileSelected();
    int GetSelectedTileID();
    TileItem *GetSelectedTile();
    TileItem *GetTileFromID(int ID);

    bool IsListTileSelected();
    int GetSelectedListTileIndex();

    void RepopulateTileList();
    
private slots:
    void on_addTile_clicked();

    void on_brushNameInput_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void SmartButtonPushed();

    void on_removeTile_clicked();

private:
    Ui::BrushPropertiesWindow *ui;

    ResourceManager *resourceManager;

    QGraphicsScene tileList;
    QGraphicsScene *tileSelector;

    ComplexBrush *currentBrush;
    int currentListIndex;
};

#endif // BRUSHPROPERTIESWINDOW_H
