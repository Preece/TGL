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
    layers->RegisterBrushManager(ui->brushManager);
    ui->brushManager->RegisterResourceManager(resources);
    ui->brushManager->RegisterTileSelector(tileSelector);
    tileSelector->RegisterResourceManager(resources);
    ui->resourceView->RegisterResourceManager(resources);
    ui->propertyBrowser->RegisterResourceManager(resources);
    ui->layerList->RegisterResourceManager(resources);
    
    connect(tileSelector, SIGNAL(SelectionChanged(TileList)), ui->brushManager, SLOT(SetSelectedTiles(TileList)));
    connect(tileSelector, SIGNAL(SelectNewBrush(int)), ui->brushManager, SLOT(SetCurrentBrush(int)));
    connect(tileSelector, SIGNAL(RevertToPreviousSingleTileBrush()), ui->brushManager, SLOT(RevertToPreviousSingleTileBrush()));

    connect(layers, SIGNAL(SelectNewTile(TileCoord)), tileSelector, SLOT(SelectNewTile(TileCoord)));

    connect(resources, SIGNAL(TileUpdated(int,int,int,TileCoord)), layers, SLOT(UpdateTile(int,int,int,TileCoord)));
    connect(resources->GetClipboard(), SIGNAL(PasteTiles(QList<Tile>)), ui->brushManager, SLOT(PasteTiles(QList<Tile>)));
    connect(resources, SIGNAL(PreviewTileUpdated(int,int,TileCoord)), layers, SLOT(UpdatePreviewTile(int,int,TileCoord)));
    connect(resources, SIGNAL(SelectPreviewItems()), layers, SLOT(SelectPreviewItems()));
    connect(resources, SIGNAL(UpdateSelectionGeometry(QRect)), layers, SLOT(UpdateSelectionGeometry(QRect)));
    connect(resources, SIGNAL(ClearEraserPreview()), layers, SLOT(ClearEraserPreview()));
    connect(resources, SIGNAL(DrawEraserPreview(int,int)), layers, SLOT(DrawEraserPreview(int,int)));
    connect(resources, SIGNAL(LayerSizeUpdated(int,int)), layers, SLOT(UpdateSceneSize(int,int)));
    connect(resources, SIGNAL(ResourceAdded(int)), ui->resourceView, SLOT(AddResource(int)));

    connect(resources, SIGNAL(LayerAdded(int)), ui->layerList, SLOT(AddLayer(int)));
    connect(resources, SIGNAL(LayerRemoved(int)), ui->layerList, SLOT(RemoveLayer(int)));

    connect(ui->addLayerButton, SIGNAL(clicked()), ui->actionAdd_Layer, SLOT(trigger()));

    connect(ui->layerList, SIGNAL(LayerSelectionChanged(int)), resources, SLOT(SetLayerSelection(int)));
    connect(ui->layerList, SIGNAL(LayerSelectionChanged(int)), layers, SLOT(SetLayerSelection(int)));

    connect(ui->brushManager, SIGNAL(SelectionCut(QList<Tile>)), resources->GetClipboard(), SLOT(Copy(QList<Tile>)));
    connect(ui->gridToggle, SIGNAL(toggled(bool)), layers, SLOT(ToggleGrid(bool)));
    connect(ui->actionSelect_Tileset, SIGNAL(triggered()), tileSelector, SLOT(SelectTileset()));
    connect(ui->selectionTool, SIGNAL(toggled(bool)), layers, SLOT(ToggleSelectionMode(bool)));
    connect(ui->levelView, SIGNAL(TraverseTileHistory(bool)), tileSelector, SLOT(TraverseTileHistory(bool)));

    connect(resources, SIGNAL(LayerVisibilityChanged(int,bool)), layers, SLOT(UpdateLayerVisibility(int,bool)));

    ui->levelView->setScene(layers);
    ui->levelView->setMouseTracking(true);

    ui->miniMap->setScene(layers);

    ui->tileSelectorView->setScene(tileSelector);

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

    ui->brushManager->SetCurrentBrush(0);
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

void MainWindow::CenterMinimapOnLevel()
{
    QPointF topLeft     = ui->levelView->mapToScene( 0, 0 );
    QPointF bottomRight = ui->levelView->mapToScene( ui->levelView->viewport()->width() - 1, ui->levelView->viewport()->height() - 1 );
    QRectF rect(topLeft, bottomRight);

    int centerX = rect.left() + (rect.width() / 2);
    int centerY = rect.top() + (rect.height() / 2);

    ui->miniMap->centerOn(centerX, centerY);
}

void MainWindow::SetToolSelection(QCursor newCursor, int newSelection)
{
    ui->toolGroup->button(newSelection)->setChecked(true);
    ui->levelView->SetCursor(newCursor);
}


void MainWindow::on_actionCut_triggered()
{
    ui->brushManager->CutTiles();
    resources->ClearPreview();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->brushManager->CopyTiles();
}

void MainWindow::on_actionPaste_triggered()
{
    resources->GetClipboard()->Paste();
}
