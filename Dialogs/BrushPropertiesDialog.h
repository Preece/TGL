#ifndef BRUSHPROPERTIESWINDOW_H
#define BRUSHPROPERTIESWINDOW_H

#include <QDialog>
#include <QGraphicsScene>

#include "../../Model/ResourceController.h"

#include "../LevelEditor/Brushes/ScatterBrush.h"
#include "../LevelEditor/Brushes/SmartBrush.h"

#include "../../Toolbox/TileSelectorScene.h"
#include "../../Toolbox/TileWidgetItem.h"

namespace Ui {
class BrushPropertiesDialog;
}

class BrushPropertiesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit BrushPropertiesDialog(QWidget *parent = 0);
    ~BrushPropertiesDialog();

    void RegisterTileSelector(TileSelectorScene *selector);
    void RegisterResourceManager(ResourceController *newRM) { resourceController = newRM; }

    void NewBrush(ComplexBrush *newBrush);
    void EditBrush(ComplexBrush *editBrush);

    void SetListIndex(int newIndex) { currentListIndex = newIndex; }

    void ShowScatterControls();
    void ShowSmartControls();
    void ShowReplacerControls();
    void ShowMatrixControls();

    bool IsTileSelected();
    TileWidgetItem *GetSelectedTile();
    TileWidgetItem *GetTileFromOrigin(TileCoord coord);

    bool IsListTileSelected();
    int GetSelectedListTileIndex();

    void RepopulateTileList();
    
private slots:
    void on_addTile_clicked();

    void on_brushNameInput_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void SmartButtonPushed();

    void on_removeTile_clicked();

    void on_dirtyTilesButton_clicked();

    void on_cleanTilesButton_clicked();

private:
    Ui::BrushPropertiesDialog *ui;

    ResourceController *resourceController;

    QGraphicsScene tileList;
    TileSelectorScene *tileSelector;

    ComplexBrush *currentBrush;
    int currentListIndex;
};

#endif // BRUSHPROPERTIESWINDOW_H
