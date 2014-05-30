#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //create a resource manager
    resources               = new ResourceController;
    tileController          = new TileController;
    tileSelector            = new TileSelectorScene;
    tileScene               = new TileScene;
    exporter                = new JSONExporter;

    //register the resource manager with the various modules. They will
    //keep themselves in sync with the resource manager
    tileController->        RegisterResourceController(resources);
    tileSelector->          RegisterResourceController(resources);
    ui->resourceView->      RegisterResourceController(resources);
    ui->propertyBrowser->   RegisterResourceController(resources);
    ui->layerList->         RegisterResourceController(resources);

    ui->brushController->      RegisterTileController(tileController);
    tileScene->             RegisterTileController(tileController);

    tileScene->             RegisterBrushController(ui->brushController);
    ui->brushController->      RegisterTileSelector(tileSelector);


    connect(tileScene,                  SIGNAL(SelectNewTile(TileCoord)),   tileSelector,               SLOT(SelectNewTile(TileCoord)));
    connect(ui->layerList,              SIGNAL(LayerSelectionChanged(int)), tileController,             SLOT(UpdateLayerSelection(int)));
    connect(ui->layerList,              SIGNAL(LayerSelectionChanged(int)), tileScene,                  SLOT(UpdateLayerSelection(int)));
    connect(ui->gridToggle,             SIGNAL(toggled(bool)),              tileScene,                  SLOT(ToggleGrid(bool)));
    connect(ui->actionSelect_Tileset,   SIGNAL(triggered()),                this,                       SLOT(PromptForTileset()));
    connect(ui->selectionTool,          SIGNAL(toggled(bool)),              tileScene,                  SLOT(ToggleSelectionMode(bool)));
    connect(ui->levelView,              SIGNAL(TraverseTileHistory(bool)),  tileSelector,               SLOT(TraverseTileHistory(bool)));
    connect(resources->GetClipboard(),  SIGNAL(PasteTiles(QList<Tile>)),    ui->brushController,        SLOT(PasteTiles(QList<Tile>)));
    connect(ui->brushController,        SIGNAL(SelectionCut(QList<Tile>)),  resources->GetClipboard(),  SLOT(Copy(QList<Tile>)));
    connect(ui->layerList,              SIGNAL(LayerVisibilityChanged(int,bool)), tileScene,            SLOT(UpdateLayerVisibility(int,bool)));

    //the layer must be added to the TileScene first
    connect(ui->actionAdd_Layer,        SIGNAL(triggered()),                resources,                  SLOT(AddTileLayer()));
    connect(resources,                  SIGNAL(LayerAdded(int)),            tileScene,                  SLOT(AddLayer(int)));
    connect(resources,                  SIGNAL(LayerAdded(int)),            ui->layerList,              SLOT(AddLayer(int)));

    connect(resources,                  SIGNAL(LayerRemoved(int)),          tileScene,                  SLOT(RemoveLayer(int)));
    connect(resources,                  SIGNAL(LayerRemoved(int)),          ui->layerList,              SLOT(RemoveLayer(int)));

    ui->levelView->setScene(tileScene);
    ui->levelView->setMouseTracking(true);

    ui->miniMap->setScene(tileScene);
    ui->tileSelectorView->setScene(tileSelector);
    ui->resourceView->RepopulateEverything();

    //assign IDs to each child in the toolgroup
    ui->toolGroup->setId(ui->pencilTool,        0);
    ui->toolGroup->setId(ui->eraserTool,        1);
    ui->toolGroup->setId(ui->bucketTool,        2);
    ui->toolGroup->setId(ui->lineTool,          3);
    ui->toolGroup->setId(ui->stampTool,         4);
    ui->toolGroup->setId(ui->eyedropperTool,    5);
    ui->toolGroup->setId(ui->selectionTool,     6);
    ui->toolGroup->setId(ui->scatterTool,       7);
    ui->toolGroup->setId(ui->scatterFillTool,   8);
    ui->toolGroup->setId(ui->replacerTool,      9);
    ui->toolGroup->setId(ui->matrixBrushTool,   10);
    ui->toolGroup->setId(ui->smartBrushTool,    11);

    ui->brushController->SetCurrentBrush(0);

    statusBar()->hide();
    ui->actionAdd_Layer->trigger();
    ui->brushController->GetPropertiesDialog()->setStyleSheet(styleSheet());

    SetupKeyboardShortcuts();
}

MainWindow::~MainWindow()
{
    resources->DestroyAllResources();
    
    delete resources;
    delete tileController;
    delete tileScene;
    delete tileSelector;
    delete exporter;

    delete ui;
}

void MainWindow::on_actionUndo_triggered()
{
    if(resources)
    {
        resources->Undo();
        //RepopulateEverything();
    }
}

void MainWindow::on_actionRedo_triggered()
{
    if(resources)
    {
        resources->Redo();
        //RepopulateEverything();
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    exporter->Export(resources, QFileDialog::getSaveFileName(this));
}

void MainWindow::on_actionOpen_triggered()
{
    if(QMessageBox::warning(this, "Open File", "Any unsaved progress will be lost! Continue?") == QMessageBox::Ok)
    {
        resources->DestroyAllResources();
        exporter->Import(resources, QFileDialog::getOpenFileName(this));
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

void MainWindow::CenterMinimapOnLevel()
{
    QPointF topLeft     = ui->levelView->mapToScene(0, 0);
    QPointF bottomRight = ui->levelView->mapToScene(ui->levelView->viewport()->width() - 1, ui->levelView->viewport()->height() - 1);
    QRectF rect(topLeft, bottomRight);

    int centerX = rect.left() + (rect.width() / 2);
    int centerY = rect.top() + (rect.height() / 2);

    ui->miniMap->centerOn(centerX, centerY);
}

void MainWindow::SetToolSelection(QCursor newCursor, int newSelection)
{
    ui->toolGroup->button(newSelection)->setChecked(true);
    ui->levelView->SetCursor(newCursor);
    tileScene->RefreshPreview();
}

void MainWindow::PromptForTileset()
{
    tileSelector->SelectTileset(this);
}


void MainWindow::on_actionCut_triggered()
{
    ui->brushController->CutTiles();
    tileController->ClearPreview();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->brushController->CopyTiles();
}

void MainWindow::on_actionPaste_triggered()
{
    resources->GetClipboard()->Paste();
}

void MainWindow::on_toolBox_currentChanged(int index)
{
    switch(index)
    {
    case 0: //resources
        ui->resourceView->RefreshNames();
        break;

    case 1: //tile painting
        ui->layerList->RefreshNames();
        break;

    default:
        break;
    }
}

void MainWindow::on_zoomSlider_valueChanged(int value)
{
    if(value == 10)
        ui->zoomLabel->setText(QString("100%"));
    else if(value < 10)
        ui->zoomLabel->setText(QString::number(value* 10) + QString("%"));
    else if(value > 10)
        ui->zoomLabel->setText(QString::number((value - 9) * 100) + QString("%"));
}

void MainWindow::on_removeLayerButton_clicked()
{
    if(ui->layerList->GetSelectedID() == 0)
        return;

    if(QMessageBox::critical(this, "Delete Layer", "Are you sure you want to delete the selected layer?", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok)
        resources->DeleteTileLayer(ui->layerList->GetSelectedID());
}

void MainWindow::SetupKeyboardShortcuts()
{
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_1), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->pencilTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_2), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->eraserTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_3), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->bucketTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_4), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->lineTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_5), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->stampTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_6), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->eyedropperTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_7), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->selectionTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_Exclam), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->scatterTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_At), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->scatterFillTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_NumberSign), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->replacerTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_Dollar), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->matrixBrushTool, SLOT(click()));

    shortcut = new QShortcut(QKeySequence(Qt::Key_Percent), this);
    shortcut->setContext(Qt::ApplicationShortcut);
    connect(shortcut, SIGNAL(activated()), ui->smartBrushTool, SLOT(click()));
}
