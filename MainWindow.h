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
    
private slots:

    void on_actionProperties_triggered();

    void UpdateSelectedTile();

    void on_gridToggle_toggled(bool checked);

    void on_addLayerButton_clicked();

    void on_layerSelector_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;

    //Dialogs
    LevelPropertiesDialog *levelPropertiesWindow;

    ResourceManager *resources;

    LayerManager *layers;
    QGraphicsScene *tileSelector;
};

#endif // MAINWINDOW_H
