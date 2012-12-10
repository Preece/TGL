#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //zero out these pointers
    levelPropertiesWindow = 0;

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

    //when the selection changes in tileSelector, notify the layer manager
    connect(tileSelector, SIGNAL(selectionChanged()), this, SLOT(UpdateSelectedTile()));

    ui->toolGroup->setId(ui->pencilTool, 0);
    ui->toolGroup->setId(ui->eyedropperTool, 1);
    ui->toolGroup->setId(ui->brushTool, 2);
    ui->toolGroup->setId(ui->bucketTool, 3);
    ui->toolGroup->setId(ui->eraserButton, 4);
    ui->toolGroup->setId(ui->pointerTool, 5);

    connect(ui->toolGroup, SIGNAL(buttonPressed(int)), this, SLOT(UpdateToolSelection(int)));
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
    layers->SetSelectedTile(GetSelectedTileItem());
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

void MainWindow::on_gridToggle_toggled(bool checked)
{
    layers->ToggleGrid(checked);
}

void MainWindow::on_addLayerButton_clicked()
{
    layers->AddLayer("Test");


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

void MainWindow::UpdateToolSelection(int newTool)
{
    layers->SetTool(newTool);
}

void MainWindow::on_pencilTool_clicked()
{
    layers->SetTool(0);
}
