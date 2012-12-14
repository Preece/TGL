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
    layers->setSceneRect(0, 0, 100, 100);
    layers->RegisterResourceManager(resources);

    currentBrush = &pencil;
    ui->levelView->setMouseTracking(true);

    //when the selection changes in tileSelector, notify the layer manager
    connect(tileSelector, SIGNAL(selectionChanged()), this, SLOT(UpdateSelectedTile()));

    connect(ui->toolGroup, SIGNAL(buttonPressed(int)), this, SLOT(UpdateToolSelection()));
    UpdateToolSelection();

    connect(layers, SIGNAL(SelectNewTile(int)), this, SLOT(SelectNewTile(int)));
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
        pencil.SetSelectedTileID(GetSelectedTileItem()->GetTileID());
        bucket.SetSelectedTileID(GetSelectedTileItem()->GetTileID());
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
    layers->SetBrush(currentBrush);
}

void MainWindow::on_pencilTool_clicked()
{
    currentBrush = &pencil;
    UpdateToolSelection();

    //change the cursor
    ui->levelView->setCursor(QCursor(QPixmap(":\Icons\Icons\pencil.png")));
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
    currentBrush = &bucket;
    UpdateToolSelection();
}

void MainWindow::on_eraserButton_clicked()
{
    currentBrush = &eraser;
    UpdateToolSelection();
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
