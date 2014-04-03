#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create a resource manager
    resources               = new ResourceManager;
    levelPropertiesWindow   = new LevelPropertiesDialog;
    layerPropertiesWindow   = new LayerProperties;
    tileSelector            = new TileSelectorScene;
    layers                  = new LayerManager;

    //register the resource manager with the resource tab. The resource tab will
    //keep itself in synch with the resource manager
    ui->resourceTab->RegisterResourceManager(resources);
    levelPropertiesWindow->RegisterResourceManager(resources);
    layers->RegisterResourceManager(resources);
    ui->brushProperties->RegisterResourceManager(resources);
    tileSelector->RegisterResourceManager(resources);
    
    ui->resourceTab->RegisterTileSelector(tileSelector);
    ui->brushProperties->RegisterTileSelector(tileSelector);

    connect(ui->resourceTab, SIGNAL(NewSpriteButtonClicked()), ui->actionAdd_Sprite, SLOT(trigger()));
    connect(tileSelector, SIGNAL(SelectionChanged(TileList)), ui->brushProperties, SLOT(SetSelectedTiles(TileList)));
    connect(ui->brushProperties, SIGNAL(BrushChanged()), this, SLOT(UpdateToolSelection()));
    connect(ui->toolGroup, SIGNAL(buttonPressed(int)), this, SLOT(UpdateToolSelection()));
    connect(layers, SIGNAL(SelectNewTile(TileCoord)), tileSelector, SLOT(SelectNewTile(TileCoord)));
    
    ui->levelView->setScene(layers);
    ui->levelView->setMouseTracking(true);
    
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/pencil.png"), 1, 1);
    ui->levelView->setCursor(tempCur);

    zoomLevel = 1;
    //QScrollBar *scroll = ui->levelView->horizontalScrollBar();
    //connect(scroll, SIGNAL(valueChanged(int)), )
}

MainWindow::~MainWindow()
{
    delete ui;

    resources->DestroyAllResources();
    
    delete resources;
    //call a cleanup function?
    delete layers;
    delete tileSelector;
    delete layerPropertiesWindow;
    delete levelPropertiesWindow;
}

void MainWindow::on_actionProperties_triggered()
{
    levelPropertiesWindow->LoadValues();
    levelPropertiesWindow->exec();
}

void MainWindow::RepopulateLayerSelector()
{
    ui->layerSelector->clear();

    for(int i = 0; i < layers->GetLayerCount(); i++)
    {
        QListWidgetItem *tempItem = new QListWidgetItem;
        tempItem->setText(layers->GetLayerName(i));

        tempItem->setFlags(tempItem->flags() | Qt::ItemIsUserCheckable);
        tempItem->setCheckState(Qt::Checked);

        ui->layerSelector->addItem(tempItem);

        //select the latest added layer, in the layer manager and the list view
        ui->layerSelector->setItemSelected(tempItem, true);
        layers->SetLayerSelection(i);
    }
}

bool MainWindow::IsLayerSelected()
{
    if(ui->layerSelector->currentRow() != -1)
        return true;

    return false;
}

void MainWindow::on_gridToggle_toggled(bool checked)
{
    layers->ToggleGrid(checked);
}

void MainWindow::on_addLayerButton_clicked()
{
    //create a new tile layer for the model
    TileLayer *newLayer = new TileLayer;

    //and pass the new tile layer model into the editor window
    layerPropertiesWindow->NewLayer(newLayer);

    //execute the window, and check if the changes were accepted
    if(layerPropertiesWindow->exec() == QDialog::Accepted)
    {
        //if so add the new layer to the model
        resources->AddTileLayer(newLayer);
        
        //and give a reference to the layer manager
        layers->AddLayer(newLayer);
    }
    else
    {
        delete newLayer;
    }

    RepopulateLayerSelector();
}

void MainWindow::on_layerSelector_currentRowChanged(int currentRow)
{
    layers->SetLayerSelection(currentRow);
}

void MainWindow::on_layerSelector_itemClicked(QListWidgetItem *item)
{
    if(item->checkState() == Qt::Checked)
        layers->ToggleLayerVisibility(ui->layerSelector->row(item), true);
    else
        layers->ToggleLayerVisibility(ui->layerSelector->row(item), false);
}

void MainWindow::UpdateToolSelection()
{
    layers->SetBrush(ui->brushProperties->GetCurrentBrush());
}

void MainWindow::on_editLayerButton_clicked()
{
    if(IsLayerSelected())
    {
        TileLayer *tempLayer = resources->GetLayerByIndex(ui->layerSelector->currentRow());

        if(tempLayer)
        {
            layerPropertiesWindow->EditLayer(tempLayer);
            layerPropertiesWindow->exec();

            layers->UpdateLayerOpacity(tempLayer);
        }

        RepopulateLayerSelector();
    }
}

void MainWindow::on_deleteLayerButton_clicked()
{
    if(IsLayerSelected())
    {
        TileLayer *tempLayer = resources->GetLayerByIndex(ui->layerSelector->currentRow());

        if(tempLayer)
        {
            //remove the layer from the layer manager (which will take it out of the RM)
            layers->RemoveLayer(tempLayer);

            //repopulate the layer selector
            RepopulateLayerSelector();
        }
    }
}

void MainWindow::on_zoomInTool_clicked()
{
    //check that the zoom level is not too big
    if(zoomLevel < 1)
    {
        //reset the scale
        ui->levelView->scale(1/zoomLevel, 1/zoomLevel);

        //increase the zoom level
        zoomLevel += 0.1;

        ui->zoomLevelLabel->setText(QString::number(zoomLevel * 100) + "% Zoom");

        //set the new scale
        ui->levelView->scale(zoomLevel, zoomLevel);
    }
}

void MainWindow::on_zoomOutTool_clicked()
{
    //check that the zoom level is not too small
    if(zoomLevel > 0.2)
    {
        //reset the scale
        ui->levelView->scale(1/zoomLevel, 1/zoomLevel);

        zoomLevel -= 0.1;

        ui->zoomLevelLabel->setText(QString::number(zoomLevel * 100) + "% Zoom");

        //set the new scale
        ui->levelView->scale(zoomLevel, zoomLevel);
    }
}

void MainWindow::on_actionUndo_triggered()
{
    if(resources)
    {
        resources->Undo();
        RepopulateEverything();
    }
}

void MainWindow::on_actionRedo_triggered()
{
    if(resources)
    {
        resources->Redo();
        RepopulateEverything();
    }
}

void MainWindow::RepopulateEverything()
{
    //RepopulateObjects();
    RepopulateLayerSelector();

    ui->resourceTab->RepopulateImageSelector();
    ui->resourceTab->RepopulateSpriteSelector();
    ui->resourceTab->RepopulateTileSelector();

    layers->RepopulateAllLayers();
}

void MainWindow::on_pencilTool_clicked()
{
    ui->brushProperties->SetCurrentBrush(0);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/pencil.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_bucketTool_clicked()
{
    ui->brushProperties->SetCurrentBrush(2);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/bucket.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_eraserButton_clicked()
{
    ui->brushProperties->SetCurrentBrush(3);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/eraser.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_lineTool_clicked()
{
    ui->brushProperties->SetCurrentBrush(10);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/line.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_replacerTool_clicked()
{
    ui->brushProperties->SetCurrentBrush(9);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/pencil.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_matrixBrushButton_clicked()
{
    ui->brushProperties->SetCurrentBrush(11);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/pencil.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_scatterTool_clicked()
{
    ui->brushProperties->SetCurrentBrush(6);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/pencil.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_brushTool_clicked()
{
    ui->brushProperties->SetCurrentBrush(7);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/brush.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_scatterFillTool_clicked()
{
    ui->brushProperties->SetCurrentBrush(8);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/bucket.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_pointerTool_clicked()
{
    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/selector.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::on_eyedropperTool_clicked()
{
    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/eyedropper.png"), 14, 14);
    ui->levelView->setCursor(tempCur);
}
