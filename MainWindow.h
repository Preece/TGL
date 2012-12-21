#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QGraphicsScene>

#include "Model/Sprite.h"
#include "Model/ObjectInstance.h"
#include "Model/ObjectPrototype.h"
#include "Model/ResourceManager.h"
#include "LevelEditor/LayerManager.h"
#include "LevelEditor/LayerProperties.h"

#include "LevelEditor/Brushes/TileBrush.h"
#include "LevelEditor/Brushes/PencilBrush.h"
#include "LevelEditor/Brushes/FillBrush.h"
#include "LevelEditor/Brushes/EraserBrush.h"

#include "SpriteEditor/SpriteEditor.h"
#include "LevelPropertiesDialog.h"
#include "ObjectEditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool IsTileSelected();
    TileItem *GetSelectedTileItem();

    void RepopulateLayerSelector();
    bool IsLayerSelected();
    
private slots:

    void on_actionProperties_triggered();

    void UpdateSelectedTile();

    void on_gridToggle_toggled(bool checked);

    void on_addLayerButton_clicked();

    void on_layerSelector_currentRowChanged(int currentRow);

    void on_layerSelector_itemClicked(QListWidgetItem *item);

    void UpdateToolSelection();

    void on_pencilTool_clicked();

    void SelectNewTile(int ID);

    void on_bucketTool_clicked();

    void on_eraserButton_clicked();

    void on_editLayerButton_clicked();

    void on_deleteLayerButton_clicked();

    void on_scatterTool_clicked();

    void on_brushTool_clicked();

    void on_scatterFillTool_clicked();

private:
    Ui::MainWindow *ui;

    //Dialogs
    LevelPropertiesDialog *levelPropertiesWindow;
    LayerProperties *layerPropertiesWindow;

    ResourceManager *resources;

    LayerManager *layers;
    QGraphicsScene *tileSelector;
};

#endif // MAINWINDOW_H
