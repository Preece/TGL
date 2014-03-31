#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //zero out these pointers
    levelPropertiesWindow = NULL;
    layerPropertiesWindow = NULL;

    //create a resource manager
    resources = new ResourceManager;

    //register the resource manager with the resource tab. The resource tab will
    //keep itself in synch with the resource manager
    ui->resourceTab->RegisterResourceManager(resources);

    //attach the resource manager to the resource view
    ui->resourceView->RegisterResourceManager(resources);
    ui->resourceView->RepopulateEverything();

    //connect the add sprite button in the resource tab to the add sprite action
    connect(ui->resourceTab, SIGNAL(NewSpriteButtonClicked()), ui->actionAdd_Sprite, SLOT(trigger()));

    tileSelector = new TileSelectorScene;
    ui->resourceTab->RegisterTileSelector(tileSelector);

    //the layer manager is a derivative of QGraphicsScene. It coordinates all the
    //graphical representations of the layers, which are QGraphicsItemGroups
    layers = new LayerManager;
    ui->levelView->setScene(layers);
    layers->setSceneRect(0, 0, 0, 0);
    layers->RegisterResourceManager(resources);

    //this will make sure the mouse events are sent to the level view
    ui->levelView->setMouseTracking(true);

    ui->brushProperties->RegisterTileSelector(tileSelector);
    ui->brushProperties->RegisterResourceManager(resources);

    //when the selection changes in tileSelector, notify the layer manager
    connect(tileSelector, SIGNAL(selectionChanged()), this, SLOT(UpdateSelectedTile()));
    connect(ui->brushProperties, SIGNAL(BrushChanged()), this, SLOT(UpdateToolSelection()));

    connect(ui->gridToggle, SIGNAL(toggled(bool)), layers, SLOT(ToggleGrid(bool)));

    connect(ui->toolGroup, SIGNAL(buttonPressed(int)), this, SLOT(UpdateToolSelection()));
    UpdateToolSelection();

    connect(layers, SIGNAL(SelectNewTile(TileCoord)), this, SLOT(SelectNewTile(TileCoord)));

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

    if(layerPropertiesWindow)
        delete layerPropertiesWindow;
}

bool MainWindow::IsTileSelected()
{
    if(tileSelector->selectedItems().count() > 0)
        return true;

    return false;
}

void MainWindow::on_actionProperties_triggered()
{
    if(!levelPropertiesWindow)
    {
        levelPropertiesWindow = new LevelPropertiesDialog;
        levelPropertiesWindow->RegisterResourceManager(resources);
    }

    levelPropertiesWindow->LoadValues();
    levelPropertiesWindow->exec();
}

void MainWindow::UpdateSelectedTile()
{
    //this function triggers when the tile selection changes

    //if anything is selected
    if(tileSelector->selectedItems().count() > 0)
    {
        //inform the layer manager
        layers->SetSelectedTile(GetSelectedTileItem());

        //inform the brush properties widget
        ui->brushProperties->SetSelectedTileOrigin(GetSelectedTileItem()->GetTileOrigin());
    }
}

TileWidgetItem *MainWindow::GetSelectedTileItem()
{
    if(IsTileSelected())
    {
        return dynamic_cast<TileWidgetItem*>(tileSelector->selectedItems()[0]);
    }

    return NULL;
}

bool MainWindow::IsLayerSelected()
{
    //if anything is selected
    if(ui->resourceView->selectedItems().count() > 0)
        if(resources->GetTileLayer(ui->resourceView->GetSelectedID()))
            return true;

    return false;
}

void MainWindow::on_addLayerButton_clicked()
{
    //if the layer properties window has not yet been created
    if(layerPropertiesWindow == NULL)
    {
        //create it
        layerPropertiesWindow = new LayerProperties;
    }

    //then create a new tile layer for the model
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

        layers->UpdateLayerOpacity(newLayer);

        layers->setSceneRect(0, 0, resources->GetLevelProperties()->GetMapWidth() * resources->GetLevelProperties()->GetTileWidth(),
                             resources->GetLevelProperties()->GetMapHeight() * resources->GetLevelProperties()->GetTileHeight());
    }
    else
    {
        delete newLayer;
    }

    //refresh the resource viewer. In the future, this could perhaps only refresh the layer section
    ui->resourceView->RepopulateEverything();
}

void MainWindow::UpdateToolSelection()
{
    layers->SetBrush(ui->brushProperties->GetCurrentBrush());
}

void MainWindow::on_pencilTool_clicked()
{
    ui->brushProperties->SetCurrentBrush(0);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/pencil.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::SelectNewTile(TileCoord origin)
{
    int tileW = resources->GetLevelProperties()->GetTileWidth();
    int tileH = resources->GetLevelProperties()->GetTileHeight();

    //find the x and y position of the tile
    int tileX = (tileW * origin.first) + tileW - 1;
    int tileY = (tileH * origin.second) + tileH - 1;

    tileSelector->clearSelection();

    //find that tile based on position
    QGraphicsItem *tempTileItem = tileSelector->itemAt(tileX, tileY);

    //select the new tile
    if(tempTileItem)
        tempTileItem->setSelected(true);

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

void MainWindow::on_editLayerButton_clicked()
{
    if(layerPropertiesWindow == NULL)
    {
        layerPropertiesWindow = new LayerProperties;
    }

    if(IsLayerSelected())
    {
        TileLayer *tempLayer = resources->GetTileLayer(ui->resourceView->GetSelectedID());

        if(tempLayer)
        {
            layerPropertiesWindow->EditLayer(tempLayer);
            layerPropertiesWindow->exec();

            layers->UpdateLayerOpacity(tempLayer);
        }

        ui->resourceView->RepopulateEverything();
    }
}

void MainWindow::on_deleteLayerButton_clicked()
{
    if(IsLayerSelected())
    {
        TileLayer *tempLayer = resources->GetTileLayer(ui->resourceView->GetSelectedID());

        if(tempLayer)
        {
            //remove the layer from the layer manager (which will take it out of the RM)
            layers->RemoveLayer(tempLayer);

            //refresh the resource view
            ui->resourceView->RepopulateEverything();
        }
    }
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
    ui->resourceTab->RepopulateImageSelector();
    ui->resourceTab->RepopulateSpriteSelector();
    ui->resourceTab->RepopulateTileSelector();

    ui->resourceView->RepopulateEverything();

    layers->RepopulateAllLayers();
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

void MainWindow::on_resourceView_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    //get the ID from the selection
    int selectedID = ui->resourceView->GetSelectedID();

    if(selectedID)
    {
        //if the new selection is a layer, update the selection in the layer manager
        if(resources->GetTileLayer(selectedID))
            layers->SetLayerSelection(selectedID);
    }
}
