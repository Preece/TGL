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

    //connect the add sprite button in the resource tab to the add sprite action
    connect(ui->resourceTab, SIGNAL(NewSpriteButtonClicked()), ui->actionAdd_Sprite, SLOT(trigger()));

    tileSelector = new QGraphicsScene;
    ui->resourceTab->RegisterTileSelector(tileSelector);

    layers = new LayerManager;
    ui->levelView->setScene(layers);
    layers->setSceneRect(0, 0, 0, 0);
    layers->RegisterResourceManager(resources);

    ui->levelView->setMouseTracking(true);

    ui->brushProperties->RegisterTileSelector(tileSelector);
    ui->brushProperties->RegisterResourceManager(resources);

    //when the selection changes in tileSelector, notify the layer manager
    connect(tileSelector, SIGNAL(selectionChanged()), this, SLOT(UpdateSelectedTile()));
    connect(ui->brushProperties, SIGNAL(BrushChanged()), this, SLOT(UpdateToolSelection()));

    connect(ui->toolGroup, SIGNAL(buttonPressed(int)), this, SLOT(UpdateToolSelection()));
    UpdateToolSelection();

    connect(layers, SIGNAL(SelectNewTile(int)), this, SLOT(SelectNewTile(int)));

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
    if(tileSelector->selectedItems().count() > 0)
    {
        layers->SetSelectedTile(GetSelectedTileItem());
        ui->brushProperties->SetSelectedTileID(GetSelectedTileItem()->GetTileID());
    }
}

TileItem *MainWindow::GetSelectedTileItem()
{
    if(IsTileSelected())
    {
        return dynamic_cast<TileItem*>(tileSelector->selectedItems()[0]);
    }

    return NULL;
}

void MainWindow::RepopulateLayerSelector()
{
    ui->layerSelector->clear();

    QListWidgetItem *tempItem;

    for(int i = 0; i < layers->GetLayerCount(); i++)
    {
        tempItem = new QListWidgetItem;
        tempItem->setText(layers->GetLayerName(i));

        tempItem->setFlags(tempItem->flags() | Qt::ItemIsUserCheckable);
        tempItem->setCheckState(Qt::Checked);

        ui->layerSelector->addItem(tempItem);
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
    if(layerPropertiesWindow == NULL)
    {
        layerPropertiesWindow = new LayerProperties;
    }

    Layer *newLayer = new Layer;

    layerPropertiesWindow->NewLayer(newLayer);

    if(layerPropertiesWindow->exec() == QDialog::Accepted)
    {
        resources->AddLayer(newLayer);
        layers->AddLayer(newLayer);

        layers->UpdateLayerOpacity(newLayer);

        layers->setSceneRect(0, 0, resources->GetLevelProperties()->GetMapWidth() * resources->GetLevelProperties()->GetTileWidth(),
                             resources->GetLevelProperties()->GetMapHeight() * resources->GetLevelProperties()->GetTileHeight());
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

void MainWindow::on_pencilTool_clicked()
{
    ui->brushProperties->SetCurrentBrush(0);
    UpdateToolSelection();

    //change the cursor
    QCursor tempCur(QPixmap(":/Icons/Icons/pencil.png"), 1, 1);
    ui->levelView->setCursor(tempCur);
}

void MainWindow::SelectNewTile(int ID)
{
    int tileW = resources->GetLevelProperties()->GetTileWidth();
    int tileH = resources->GetLevelProperties()->GetTileHeight();

    //get a tile based on the given ID
    Tile *tempTile = resources->GetTile(ID);

    //if the tile doesn't exist, bail
    if(!tempTile)
        return;

    //find the x and y position of the tile
    int tileX = (tileW * tempTile->GetXOrigin()) + tileW - 1;
    int tileY = (tileH * tempTile->GetYOrigin()) + tileH - 1;

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
        Layer *tempLayer = resources->GetLayerByIndex(ui->layerSelector->currentRow());

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
        Layer *tempLayer = resources->GetLayerByIndex(ui->layerSelector->currentRow());

        if(tempLayer)
        {
            //remove the layer from the layer manager (which will take it out of the RM)
            layers->RemoveLayer(tempLayer);

            //repopulate the layer selector
            RepopulateLayerSelector();
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

void MainWindow::on_addObject_clicked()
{
    if(ui->resourceTab->IsObjectSelected())
    {
        ObjectInstanceItem *tempObjItem = new ObjectInstanceItem;
        ObjectInstance *tempObj = new ObjectInstance;

        tempObj->SetPosition(0, 0);
        tempObj->SetPrototypeID(ui->resourceTab->GetSelectedObject()->GetID());
        tempObjItem->SetObjectInstance(tempObj);

        resources->AddObjectInstance(tempObj);

        tempObjItem->setPixmap(resources->GetSpriteSymbol(ui->resourceTab->GetSelectedObject()->GetSpriteID()));
        //tempObjItem->setPos(100, 100);

        tempObjItem->show();
        layers->AddObjectItem(tempObjItem);
    }
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
