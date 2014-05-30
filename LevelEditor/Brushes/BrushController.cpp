#include "BrushController.h"
#include "ui_BrushController.h"

BrushController::BrushController(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BrushController)
{
    ui->setupUi(this);

    currentBrush = &pencil;
    scatterBrushIndex = 0;
    smartBrushIndex = 0;
    replacerBrushIndex = 0;
    matrixBrushIndex = 0;

    ui->scatterBrushGroup->hide();
    ui->smartBrushGroup->hide();
    ui->replacerGroup->hide();
    ui->matrixBrushGroup->hide();

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    singleTileBrush = BrushController::Pencil;

    defaultScatter.SetName("Use Selected Tiles");
    scatter.push_front(&defaultScatter);

    defaultReplacer.SetName("Use Selected Tiles");
    replacer.push_front(&defaultReplacer);

    defaultSmart.SetName("Use Selected Tiles");
    smart.push_front(&defaultSmart);

    defaultMatrix.SetName("Use Selected Tiles");
    matrix.push_front(&defaultMatrix);

    RepopulateBrushLists();

    propertiesWindow = new BrushPropertiesDialog;
    propertiesWindow->setWindowTitle("Edit Brush");
}

BrushController::~BrushController()
{
    delete ui;
    delete propertiesWindow;

    DestroyBrushes();
}

void BrushController::SetCurrentBrush(int type)
{
    ui->scatterBrushGroup->hide();
    ui->smartBrushGroup->hide();
    ui->replacerGroup->hide();
    ui->matrixBrushGroup->hide();

    switch(type)
    {
    case BrushController::Pencil:
        currentBrush = &pencil;
        singleTileBrush = BrushController::Pencil;
        break;

    case BrushController::Bucket:
        currentBrush = &bucket;
        singleTileBrush = BrushController::Bucket;
        break;

    case BrushController::Eraser:
        currentBrush = &eraser;
        break;

    case BrushController::Line:
        currentBrush = &line;
        singleTileBrush = BrushController::Line;
        break;

    case BrushController::Eyedropper:
        currentBrush = &eyedropper;
        break;

    case BrushController::Stamp:
        currentBrush = &stamp;
        break;

    case BrushController::Selector:
        currentBrush = &selector;
        break;

    case BrushController::Scatter:
        if(scatterBrushIndex < scatter.count())
        {
            scatter[scatterBrushIndex]->SetFill(false);
            currentBrush = scatter[scatterBrushIndex];
        }
        else
            currentBrush = NULL;

        ui->scatterBrushGroup->show();
        break;

    case BrushController::Smart:
        if(smartBrushIndex < smart.count())
        {
            currentBrush = smart[smartBrushIndex];
        }
        else
            currentBrush = NULL;

        ui->smartBrushGroup->show();
        break;

    case BrushController::ScatterFill:
        if(scatterBrushIndex < scatter.count())
        {
            scatter[scatterBrushIndex]->SetFill(true);
            currentBrush = scatter[scatterBrushIndex];

        }
        else
            currentBrush = NULL;

        ui->scatterBrushGroup->show();
        break;

    case BrushController::Replacer:
        if(replacerBrushIndex < replacer.count())
        {
            currentBrush = replacer[replacerBrushIndex];

        }
        else
            currentBrush = NULL;

        ui->replacerGroup->show();
        break;

    case BrushController::Matrix:
        if(matrixBrushIndex < matrix.count())
        {
            currentBrush = matrix[matrixBrushIndex];
        }
        else
            currentBrush = NULL;

        ui->matrixBrushGroup->show();
        break;

    default:
        currentBrush = &pencil;
        break;

    }

    emit BrushChanged(currentBrush->GetCursor(), type);
}

void BrushController::RevertToPreviousSingleTileBrush()
{
    SetCurrentBrush(singleTileBrush);
}

void BrushController::RepopulateBrushLists()
{
    //clear out the scatter brush list
    ui->scatterBrushCombo->clear();

    //loop over the brush list and add them all
    for(int i = 0; i < scatter.count(); i++)
    {
        ui->scatterBrushCombo->addItem(scatter[i]->GetName());
        ui->scatterBrushCombo->setCurrentIndex(i);
        scatterBrushIndex = i;
    }

    ui->scatterBrushCombo->addItem("Add New Brush...");

    ui->smartBrushCombo->clear();

    for(int i = 0; i < smart.count(); i++)
    {
        ui->smartBrushCombo->addItem(smart[i]->GetName());
        ui->smartBrushCombo->setCurrentIndex(i);
        smartBrushIndex = i;
    }

    ui->smartBrushCombo->addItem("Add New Brush...");

    ui->replacerBrushCombo->clear();

    for(int i = 0; i < replacer.count(); i++)
    {
        ui->replacerBrushCombo->addItem(replacer[i]->GetName());
        ui->replacerBrushCombo->setCurrentIndex(i);
        replacerBrushIndex = i;
    }

    ui->replacerBrushCombo->addItem("Add New Brush...");

    ui->matrixBrushCombo->clear();

    for(int i = 0; i < matrix.count(); i++)
    {
        ui->matrixBrushCombo->addItem(matrix[i]->GetName());
        ui->matrixBrushCombo->setCurrentIndex(i);
        matrixBrushIndex = i;
    }

    ui->matrixBrushCombo->addItem("Add New Brush...");
}

void BrushController::RegisterTileSelector(TileSelectorScene *selector)
{
    propertiesWindow->RegisterTileSelector(selector);

    connect(selector, SIGNAL(SelectionChanged(TileList)), this, SLOT(SetSelectedTiles(TileList)));
    connect(selector, SIGNAL(SelectNewBrush(int)), this, SLOT(SetCurrentBrush(int)));
    connect(selector, SIGNAL(RevertToPreviousSingleTileBrush()), this, SLOT(RevertToPreviousSingleTileBrush()));
}

void BrushController::RegisterTileController(TileController *newRM)
{
    tiles = newRM;
    propertiesWindow->RegisterTileController(newRM);
}

void BrushController::DestroyBrushes()
{
    for(int i = 0; i < scatter.count(); i++)
    {
        delete scatter[i];
    }

    scatter.clear();

    for(int i = 0; i < smart.count(); i++)
    {
        delete smart[i];
    }

    smart.clear();

    for(int i = 0; i < replacer.count(); i++)
    {
        delete replacer[i];
    }

    replacer.clear();

    for(int i = 0; i < matrix.count(); i++)
    {
        delete matrix[i];
    }

    matrix.clear();
}

void BrushController::SetSelectedTiles(TileList newList)
{
    if(newList.count() > 0)
    {
        pencil.SetSelectedTileOrigin(newList[0]);
        bucket.SetSelectedTileOrigin(newList[0]);
    
        stamp.CreateGrid(newList);

        //overwrite the default scatters list
        defaultScatter.AddTiles(0, newList, true);
        defaultReplacer.PushNewList(newList);

        if(currentBrush->GetType() != "scatter" &&
           currentBrush->GetType() != "smart" &&
           currentBrush->GetType() != "matrix" &&
           currentBrush->GetType() != "replacer")
        {
            //if multiple tiles were selected, go ahead and select the stamp.
            if(newList.count() > 1)
                SetCurrentBrush(BrushController::Stamp);
            else if(newList.count() == 1)
                RevertToPreviousSingleTileBrush();
        }
        
    }
}

void BrushController::CutTiles()
{
    //emit the selected tiles then clear out the selector
    emit SelectionCut(selector.GetDraggingTiles());
    selector.ClearDraggingTiles();
}

void BrushController::CopyTiles()
{
    //simply emit what is selected
    emit SelectionCut(selector.GetDraggingTiles());
}

void BrushController::PasteTiles(QList<Tile> pasteTiles)
{
    //first integrate any selected tiles
    //selector.IntegrateSelectedTiles();
    selector.SetDraggingTiles(tiles, pasteTiles);
}

void BrushController::on_overwriteCheckbox_toggled(bool checked)
{
    pencil.SetOverwrite(checked);

    for(int i = 0; i < scatter.count(); i++)
    {
        scatter[i]->SetOverwrite(checked);
    }
}

void BrushController::on_brushSizeInput_valueChanged(int arg1)
{
    pencil.SetSize(arg1);
    eraser.SetSize(arg1);
}

void BrushController::on_addScatterBrush_clicked()
{
    //create a new brush and pass it to the properties window
    ScatterBrush *tempBrush = new ScatterBrush;
    propertiesWindow->NewBrush(tempBrush);
    propertiesWindow->ShowScatterControls();

    //execute the window, and check if it was accepted
    if(propertiesWindow->exec() == QDialog::Accepted)
        scatter.append(tempBrush);
    else
        delete tempBrush;

    RepopulateBrushLists();
}

void BrushController::on_scatterBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    scatterBrushIndex = index;

    if(scatterBrushIndex < scatter.count())
    {
        currentBrush = scatter[scatterBrushIndex];
        emit BrushChanged(currentBrush->GetCursor(), BrushController::Scatter);
    }
    else
    {
        //they clicked the add brush option, so add one
        on_addScatterBrush_clicked();
    }
}

void BrushController::on_editScatterBrush_clicked()
{
    if(ui->scatterBrushCombo->currentIndex() != -1)
    {
        propertiesWindow->EditBrush(scatter[scatterBrushIndex]);
        propertiesWindow->SetListIndex(0);
        propertiesWindow->exec();

        RepopulateBrushLists();
    }
}

void BrushController::on_deleteScatterBrush_clicked()
{
    //if a brush is selected
    if(ui->scatterBrushCombo->currentIndex() != -1)
    {
        delete scatter[scatterBrushIndex];
        scatter.removeAt(scatterBrushIndex);

        RepopulateBrushLists();
    }
}

void BrushController::on_smartBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    smartBrushIndex = index;

    if(smartBrushIndex < smart.count())
    {
        currentBrush = smart[smartBrushIndex];
        emit BrushChanged(currentBrush->GetCursor(), BrushController::Smart);
    }
    else
    {
        on_addSmartBrush_clicked();
    }
}

void BrushController::on_addSmartBrush_clicked()
{
    //create a new brush and pass it to the properties window
    SmartBrush *tempBrush = new SmartBrush;
    propertiesWindow->NewBrush(tempBrush);
    propertiesWindow->ShowSmartControls();

    //execute the window, and check if it was accepted
    if(propertiesWindow->exec() == QDialog::Accepted)
        smart.append(tempBrush);
    else
        delete tempBrush;

    RepopulateBrushLists();
}

void BrushController::on_editSmartBrushes_clicked()
{
    if(ui->smartBrushCombo->currentIndex() != -1)
    {
        propertiesWindow->EditBrush(smart[smartBrushIndex]);
        propertiesWindow->SetListIndex(4);
        propertiesWindow->exec();

        RepopulateBrushLists();
    }
}

void BrushController::on_addReplacerBrush_clicked()
{
    //create a new brush and pass it to the properties window
    ReplacerBrush *tempBrush = new ReplacerBrush;
    propertiesWindow->NewBrush(tempBrush);
    propertiesWindow->ShowReplacerControls();

    //execute the window, and check if it was accepted
    if(propertiesWindow->exec() == QDialog::Accepted)
        replacer.append(tempBrush);
    else
        delete tempBrush;

    RepopulateBrushLists();
}

void BrushController::on_editReplacerBrush_clicked()
{
    if(ui->replacerBrushCombo->currentIndex() != -1)
    {
        propertiesWindow->EditBrush(replacer[replacerBrushIndex]);
        propertiesWindow->SetListIndex(0);
        propertiesWindow->exec();

        RepopulateBrushLists();
    }
}

void BrushController::on_deleteReplacerBrush_clicked()
{
    //if a brush is selected
    if(ui->replacerBrushCombo->currentIndex() != -1)
    {
        delete replacer[replacerBrushIndex];
        replacer.removeAt(replacerBrushIndex);

        RepopulateBrushLists();
    }
}

void BrushController::on_replacerBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    replacerBrushIndex = index;

    if(replacerBrushIndex < replacer.count())
    {
        currentBrush = replacer[replacerBrushIndex];
        emit BrushChanged(currentBrush->GetCursor(), BrushController::Replacer);
    }
    else
    {
        on_addReplacerBrush_clicked();
    }
}

void BrushController::on_addMatrixBrush_clicked()
{
    //create a new brush and pass it to the properties window
    MatrixBrush *tempBrush = new MatrixBrush;
    propertiesWindow->NewBrush(tempBrush);
    propertiesWindow->ShowMatrixControls();

    //execute the window, and check if it was accepted
    if(propertiesWindow->exec() == QDialog::Accepted)
        matrix.append(tempBrush);
    else
        delete tempBrush;

    RepopulateBrushLists();
}

void BrushController::on_editMatrixBrush_clicked()
{
    if(ui->matrixBrushCombo->currentIndex() != -1)
    {
        propertiesWindow->EditBrush(matrix[matrixBrushIndex]);
        propertiesWindow->SetListIndex(0);
        propertiesWindow->exec();

        RepopulateBrushLists();
    }
}

void BrushController::on_deleteMatrixBrush_clicked()
{
    //if a brush is selected
    if(ui->matrixBrushCombo->currentIndex() != -1)
    {
        delete matrix[matrixBrushIndex];
        matrix.removeAt(matrixBrushIndex);

        RepopulateBrushLists();
    }
}

void BrushController::on_matrixBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    matrixBrushIndex = index;

    if(matrixBrushIndex < matrix.count())
    {
        currentBrush = matrix[matrixBrushIndex];
        emit BrushChanged(currentBrush->GetCursor(), BrushController::Matrix);
    }
    else
    {
        on_addMatrixBrush_clicked();
    }
}
