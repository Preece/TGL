#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QGraphicsScene>
#include <QTreeWidget>
#include <QFileDialog>

#include "Model/ResourceController.h"
#include "Model/TileController.h"

#include "Dialogs/LevelPropertiesDialog.h"

#include "LevelEditor/TileScene.h"
#include "LevelEditor/Brushes/BrushManager.h"

#include "Toolbox/TileSelectorScene.h"

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

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:

    void on_actionProperties_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionAdd_Image_triggered();

    void CenterMinimapOnLevel();
    void SetToolSelection(QCursor newCursor, int newSelection);

    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();

    void on_toolBox_currentChanged(int index);
    void on_zoomSlider_valueChanged(int value);

    void on_removeLayerButton_clicked();

private:
    Ui::MainWindow *ui;

    //Dialogs
    LevelPropertiesDialog *levelPropertiesWindow;

    ResourceController *resources;
    TileController *tileController;

    TileScene *layers;
    TileSelectorScene *tileSelector;
};

#endif // MAINWINDOW_H
