#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QGraphicsScene>
#include <QTreeWidget>
#include <QFileDialog>

#include "Model/Sprite.h"
#include "Model/ResourceManager.h"
#include "LevelEditor/LayerManager.h"
#include "LevelEditor/LayerProperties.h"

#include "LevelEditor/Brushes/TileBrush.h"
#include "LevelEditor/Brushes/PencilBrush.h"
#include "LevelEditor/Brushes/FillBrush.h"
#include "LevelEditor/Brushes/EraserBrush.h"

#include "Toolbox/TileSelectorScene.h"

#include "SpriteEditor/SpriteEditor.h"
#include "LevelPropertiesDialog.h"

typedef QList<TileCoord> TileList;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void RepopulateEverything();

private slots:

    void on_actionProperties_triggered();
    void UpdateToolSelection();
    void on_pencilTool_clicked();
    void on_bucketTool_clicked();
    void on_eraserButton_clicked();
    void on_scatterTool_clicked();
    void on_brushTool_clicked();
    void on_scatterFillTool_clicked();
    void on_pointerTool_clicked();
    void on_eyedropperTool_clicked();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_lineTool_clicked();
    void on_replacerTool_clicked();
    void on_matrixBrushButton_clicked();
    void on_stampTool_clicked();
    void on_actionAdd_Image_triggered();
    void on_actionAdd_Layer_triggered();
    void on_actionDelete_Layer_triggered();
    void on_actionEdit_Layer_triggered();

    void on_selectionTool_clicked();

private:
    Ui::MainWindow *ui;

    //Dialogs
    LevelPropertiesDialog *levelPropertiesWindow;
    LayerProperties *layerPropertiesWindow;

    ResourceManager *resources;

    LayerManager *layers;
    TileSelectorScene *tileSelector;

    float zoomLevel;
};

#endif // MAINWINDOW_H
