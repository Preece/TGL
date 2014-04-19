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

    //register the resource manager with the various modules. They will
    //keep themselves in sync with the resource manager
    levelPropertiesWindow->RegisterResourceManager(resources);
    layers->RegisterResourceManager(resources);
    ui->brushManager->RegisterResourceManager(resources);
    tileSelector->RegisterResourceManager(resources);
    ui->resourceView->RegisterResourceManager(resources);
    ui->propertyBrowser->RegisterResourceManager(resources);
    
    ui->brushManager->RegisterTileSelector(tileSelector);

    connect(tileSelector, SIGNAL(SelectionChanged(TileList)), ui->brushManager, SLOT(SetSelectedTiles(TileList)));
    connect(tileSelector, SIGNAL(SelectEraser()), this, SLOT(on_eraserButton_clicked()));
    connect(layers, SIGNAL(SelectNewTile(TileCoord)), tileSelector, SLOT(SelectNewTile(TileCoord)));
    connect(resources, SIGNAL(ImageListModified()), ui->resourceView, SLOT(RepopulateImages()));
    connect(resources, SIGNAL(LayerListModified(int)), ui->resourceView, SLOT(RepopulateLayers(int)));
    connect(ui->brushManager, SIGNAL(BrushChanged(TileBrush*, QCursor)), layers, SLOT(SetBrush(TileBrush*, QCursor)));
    connect(ui->gridToggle, SIGNAL(toggled(bool)), layers, SLOT(ToggleGrid(bool)));
    connect(ui->toolGroup, SIGNAL(buttonPressed(int)), ui->brushManager, SLOT(SetCurrentBrush(int));
    connect(ui->resourceView, SIGNAL(NewLayerSelected(int)), layers, SLOT(SetLayerSelection(int)));
    connect(ui->resourceView, SIGNAL(NewResourceSelected(int)), ui->propertyBrowser, SLOT(DisplayResource(int)));
    connect(ui->actionSelect_Tileset, SIGNAL(triggered()), tileSelector, SLOT(SelectTileset()));
    connect(ui->selectionTool, SIGNAL(toggled(bool)), layers, SLOT(ToggleSelectionMode(bool)));
    
    ui->levelView->setScene(layers);
    ui->levelView->setMouseTracking(true);

    ui->miniMap->setScene(layers);
    ui->levelView->setMouseTracking(true);

    ui->tileSelectorView->setScene(tileSelector);
    
    ui->brushManager->SetCurrentBrush(Brushmanager::BrushTypes::Pencil);

    //QScrollBar *scroll = ui->levelView->horizontalScrollBar();
    //connect(scroll, SIGNAL(valueChanged(int)), )

    ui->resourceView->RepopulateEverything();
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
    tileSelector->RepopulateTileSelector();

    ui->resourceView->RepopulateEverything();

    layers->RepopulateAllLayers();
}

void MainWindow::on_actionAdd_Image_triggered()
{
    //ask the user where to load the file from.
    QString filename = QFileDialog::getOpenFileName(this, "Add Image", ".", "Portable Network Graphics (*.png)");

    //if the dialog succeeds
    if(!filename.isEmpty())
    {
        Image *tempImage = new Image;

        //load the file
        tempImage->SetImageFromFile(filename);

        //add the image to the resource manager
        resources->AddImage(tempImage);
    }
}

void MainWindow::on_actionAdd_Layer_triggered()
{
    //create a new tile layer for the model
    TileLayer *newLayer = new TileLayer;

    //execute the window, and check if the changes were accepted
    if(layerPropertiesWindow->SetupNewLayer(newLayer) == QDialog::Accepted)
    {
        //if so add the new layer to the model
        resources->AddTileLayer(newLayer);

        //and give a reference to the layer manager
        layers->AddLayer(newLayer->GetID());
    }
    else
    {
        delete newLayer;
    }
}

void MainWindow::on_actionDelete_Layer_triggered()
{
    if(ui->resourceView->IsLayerSelected())
    {
        TileLayer *tempLayer = resources->GetTileLayer(ui->resourceView->GetSelectedID());

        if(tempLayer)
        {
            //remove the layer from the layer manager (which will take it out of the RM)
            layers->RemoveLayer(tempLayer->GetID());
        }
    }
}

void MainWindow::on_actionEdit_Layer_triggered()
{
    if(ui->resourceView->IsLayerSelected())
    {
        TileLayer *tempLayer = resources->GetTileLayer(ui->resourceView->GetSelectedID());

        if(tempLayer)
        {
            layerPropertiesWindow->EditLayer(tempLayer);
            layers->UpdateLayerOpacity(tempLayer->GetID());
        }
    }
}

