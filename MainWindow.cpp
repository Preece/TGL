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
    layerPropertiesWindow   = new LayerPropertiesDialog;
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
    connect(tileSelector, SIGNAL(SelectNewBrush(int)), ui->brushManager, SLOT(SetCurrentBrush(int)));
    connect(tileSelector, SIGNAL(SelectNewBrush(int)), this, SLOT(SetToolButtonSelection(int)));
    connect(tileSelector, SIGNAL(RevertToPreviousSingleTileBrush()), ui->brushManager, SLOT(RevertToPreviousSingleTileBrush()));
    connect(layers, SIGNAL(SelectNewTile(TileCoord)), tileSelector, SLOT(SelectNewTile(TileCoord)));
    connect(resources, SIGNAL(ImageListModified()), ui->resourceView, SLOT(RepopulateImages()));
    connect(resources, SIGNAL(LayerListModified(int)), ui->resourceView, SLOT(RepopulateLayers(int)));
    connect(ui->brushManager, SIGNAL(BrushChanged(TileBrush*)), layers, SLOT(SetBrushSelection(TileBrush*)));
    connect(ui->brushManager, SIGNAL(BrushChanged(TileBrush*)), ui->levelView, SLOT(SetCursor(TileBrush*)));
    connect(ui->gridToggle, SIGNAL(toggled(bool)), layers, SLOT(ToggleGrid(bool)));
    connect(ui->toolGroup, SIGNAL(buttonPressed(int)), ui->brushManager, SLOT(SetCurrentBrush(int)));
    connect(ui->resourceView, SIGNAL(NewLayerSelected(int)), layers, SLOT(SetLayerSelection(int)));
    connect(ui->resourceView, SIGNAL(NewResourceSelected(int)), ui->propertyBrowser, SLOT(DisplayResource(int)));
    connect(ui->actionSelect_Tileset, SIGNAL(triggered()), tileSelector, SLOT(SelectTileset()));
    connect(ui->selectionTool, SIGNAL(toggled(bool)), layers, SLOT(ToggleSelectionMode(bool)));
    connect(ui->miniMap, SIGNAL(CenterMinimapOnLevel()), this, SLOT(CenterMinimapOnLevel()));
    connect(ui->levelView, SIGNAL(TraverseTileHistory(bool)), tileSelector, SLOT(TraverseTileHistory(bool)));

    //needs to be axed
    connect(resources, SIGNAL(MapSizeChanged(int,int)), layers, SLOT(UpdateLayerSizes(int,int)));
    
    ui->levelView->setScene(layers);
    ui->levelView->setMouseTracking(true);

    ui->miniMap->setScene(layers);

    ui->tileSelectorView->setScene(tileSelector);
    
    ui->brushManager->SetCurrentBrush(0);

    //QScrollBar *scroll = ui->levelView->horizontalScrollBar();
    //connect(scroll, SIGNAL(valueChanged(int)), )

    ui->resourceView->RepopulateEverything();

    //assign IDs to each child in the toolgroup
    ui->toolGroup->setId(ui->pencilTool, 0);
    ui->toolGroup->setId(ui->eraserTool, 1);
    ui->toolGroup->setId(ui->bucketTool, 2);
    ui->toolGroup->setId(ui->lineTool, 3);
    ui->toolGroup->setId(ui->stampTool, 4);
    ui->toolGroup->setId(ui->eyedropperTool, 5);
    ui->toolGroup->setId(ui->selectionTool, 6);
    ui->toolGroup->setId(ui->scatterTool, 7);
    ui->toolGroup->setId(ui->scatterFillTool, 8);
    ui->toolGroup->setId(ui->replacerTool, 9);
    ui->toolGroup->setId(ui->matrixBrushTool, 10);
    ui->toolGroup->setId(ui->smartBrushTool, 11);
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

void MainWindow::CenterMinimapOnLevel()
{
    QPointF topLeft     = ui->levelView->mapToScene( 0, 0 );
    QPointF bottomRight = ui->levelView->mapToScene( ui->levelView->viewport()->width() - 1, ui->levelView->viewport()->height() - 1 );
    QRectF rect(topLeft, bottomRight);

    int centerX = rect.left() + (rect.width() / 2);
    int centerY = rect.top() + (rect.height() / 2);

    ui->miniMap->centerOn(centerX, centerY);
}

void MainWindow::SetToolButtonSelection(int newSelection)
{
    ui->toolGroup->button(newSelection)->setChecked(true);
}

