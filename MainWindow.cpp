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
    tileScene                  = new TileScene;

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
    connect(ui->actionSelect_Tileset,   SIGNAL(triggered()),                tileSelector,               SLOT(SelectTileset()));
    connect(ui->selectionTool,          SIGNAL(toggled(bool)),              tileScene,                  SLOT(ToggleSelectionMode(bool)));
    connect(ui->levelView,              SIGNAL(TraverseTileHistory(bool)),  tileSelector,               SLOT(TraverseTileHistory(bool)));
    connect(resources->GetClipboard(),  SIGNAL(PasteTiles(QList<Tile>)),    ui->brushController,           SLOT(PasteTiles(QList<Tile>)));
    connect(ui->brushController,           SIGNAL(SelectionCut(QList<Tile>)),  resources->GetClipboard(),  SLOT(Copy(QList<Tile>)));
    connect(ui->layerList,              SIGNAL(LayerVisibilityChanged(int,bool)), tileScene,            SLOT(UpdateLayerVisibility(int,bool)));

    //the layer must be added to the TileScene first
    connect(ui->actionAdd_Layer,        SIGNAL(triggered()),                resources,                  SLOT(AddTileLayer()));
    connect(resources,                  SIGNAL(LayerAdded(int)),            tileScene,                     SLOT(AddLayer(int)));
    connect(resources,                  SIGNAL(LayerAdded(int)),            ui->layerList,              SLOT(AddLayer(int)));

    connect(resources,                  SIGNAL(LayerRemoved(int)),          tileScene,                     SLOT(RemoveLayer(int)));
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
}

MainWindow::~MainWindow()
{
    delete ui;

    resources->DestroyAllResources();
    
    delete resources;
    delete tileController;
    delete tileScene;
    delete tileSelector;
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

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_1:
        ui->brushController->SetCurrentBrush(BrushController::Pencil);
        break;

    case Qt::Key_2:
        ui->brushController->SetCurrentBrush(BrushController::Eraser);
        break;

    case Qt::Key_3:
        ui->brushController->SetCurrentBrush(BrushController::Bucket);
        break;

    case Qt::Key_4:
        ui->brushController->SetCurrentBrush(BrushController::Line);
        break;

    case Qt::Key_5:
        ui->brushController->SetCurrentBrush(BrushController::Stamp);
        break;

    case Qt::Key_6:
        ui->brushController->SetCurrentBrush(BrushController::Eyedropper);
        break;

    case Qt::Key_7:
        ui->brushController->SetCurrentBrush(BrushController::Selector);
        break;

    case Qt::Key_Exclam:
        ui->brushController->SetCurrentBrush(BrushController::Scatter);
        break;

    case Qt::Key_At:
        ui->brushController->SetCurrentBrush(BrushController::ScatterFill);
        break;

    case Qt::Key_NumberSign:
        ui->brushController->SetCurrentBrush(BrushController::Replacer);
        break;

    case Qt::Key_Dollar:
        ui->brushController->SetCurrentBrush(BrushController::Matrix);
        break;

    case Qt::Key_Percent:
        ui->brushController->SetCurrentBrush(BrushController::Smart);
        break;

    case Qt::Key_N:
        if(ui->toolBox->currentIndex() == ui->toolBox->count() - 1)
            ui->toolBox->setCurrentIndex(0);
        else
            ui->toolBox->setCurrentIndex(ui->toolBox->currentIndex() + 1);
        break;

    case Qt::Key_Plus:
        ui->zoomSlider->triggerAction(QAbstractSlider::SliderSingleStepAdd);
        //ui->zoomSlider->mo(ui->zoomSlider->sliderPosition() + 1);
        break;

    case Qt::Key_Minus:
        ui->zoomSlider->setSliderPosition(ui->zoomSlider->sliderPosition() - 1);
        break;
    }
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
