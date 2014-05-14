#include "BrushManager.h"
#include "ui_BrushManager.h"

BrushManager::BrushManager(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BrushManager)
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

    singleTileBrush = BrushManager::Pencil;

    defaultScatter.SetName("Default");
    scatter.push_front(&defaultScatter);

    defaultReplacer.SetName("Default");
    replacer.push_front(&defaultReplacer);

    defaultSmart.SetName("Default");
    smart.push_front(&defaultSmart);

    defaultMatrix.SetName("Default");
    matrix.push_front(&defaultMatrix);

    RepopulateBrushLists();
}

BrushManager::~BrushManager()
{
    delete ui;

    DestroyBrushes();
}

void BrushManager::SetCurrentBrush(int type)
{
    ui->scatterBrushGroup->hide();
    ui->smartBrushGroup->hide();
    ui->replacerGroup->hide();
    ui->matrixBrushGroup->hide();

    switch(type)
    {
    case BrushManager::Pencil:
        currentBrush = &pencil;
        singleTileBrush = BrushManager::Pencil;
        break;

    case BrushManager::Bucket:
        currentBrush = &bucket;
        singleTileBrush = BrushManager::Bucket;
        break;

    case BrushManager::Eraser:
        currentBrush = &eraser;
        break;

    case BrushManager::Line:
        currentBrush = &line;
        singleTileBrush = BrushManager::Line;
        break;

    case BrushManager::Eyedropper:
        currentBrush = &eyedropper;
        break;

    case BrushManager::Stamp:
        currentBrush = &stamp;
        break;

    case BrushManager::Selector:
        currentBrush = &selector;
        break;

    case BrushManager::Scatter:
        if(scatterBrushIndex < scatter.count())
        {
            scatter[scatterBrushIndex]->SetFill(false);
            currentBrush = scatter[scatterBrushIndex];
        }
        else
            currentBrush = NULL;

        ui->scatterBrushGroup->show();
        break;

    case BrushManager::Smart:
        if(smartBrushIndex < smart.count())
        {
            currentBrush = smart[smartBrushIndex];
        }
        else
            currentBrush = NULL;

        ui->smartBrushGroup->show();
        break;

    case BrushManager::ScatterFill:
        if(scatterBrushIndex < scatter.count())
        {
            scatter[scatterBrushIndex]->SetFill(true);
            currentBrush = scatter[scatterBrushIndex];

        }
        else
            currentBrush = NULL;

        ui->scatterBrushGroup->show();
        break;

    case BrushManager::Replacer:
        if(replacerBrushIndex < replacer.count())
        {
            currentBrush = replacer[replacerBrushIndex];

        }
        else
            currentBrush = NULL;

        ui->replacerGroup->show();
        break;

    case BrushManager::Matrix:
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

void BrushManager::RevertToPreviousSingleTileBrush()
{
    SetCurrentBrush(singleTileBrush);
}

void BrushManager::RepopulateBrushLists()
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

void BrushManager::RegisterTileSelector(TileSelectorScene *selector)
{
    propertiesWindow.RegisterTileSelector(selector);

    connect(selector, SIGNAL(SelectionChanged(TileList)), this, SLOT(SetSelectedTiles(TileList)));
    connect(selector, SIGNAL(SelectNewBrush(int)), this, SLOT(SetCurrentBrush(int)));
    connect(selector, SIGNAL(RevertToPreviousSingleTileBrush()), this, SLOT(RevertToPreviousSingleTileBrush()));
}

void BrushManager::RegisterTileController(TileController *newRM)
{
    tiles = newRM;
}

void BrushManager::DestroyBrushes()
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

void BrushManager::SetSelectedTiles(TileList newList)
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
                SetCurrentBrush(BrushManager::Stamp);
            else if(newList.count() == 1)
                RevertToPreviousSingleTileBrush();
        }
        
    }
}

void BrushManager::CutTiles()
{
    //emit the selected tiles then clear out the selector
    emit SelectionCut(selector.GetDraggingTiles());
    selector.ClearDraggingTiles();
}

void BrushManager::CopyTiles()
{
    //simply emit what is selected
    emit SelectionCut(selector.GetDraggingTiles());
}

void BrushManager::PasteTiles(QList<Tile> pasteTiles)
{
    //first integrate any selected tiles
    //selector.IntegrateSelectedTiles();
    selector.SetDraggingTiles(tiles, pasteTiles);
}

void BrushManager::on_overwriteCheckbox_toggled(bool checked)
{
    pencil.SetOverwrite(checked);

    for(int i = 0; i < scatter.count(); i++)
    {
        scatter[i]->SetOverwrite(checked);
    }
}

void BrushManager::on_brushSizeInput_valueChanged(int arg1)
{
    pencil.SetSize(arg1);
    eraser.SetSize(arg1);
}

void BrushManager::on_addScatterBrush_clicked()
{
    //create a new brush and pass it to the properties window
    ScatterBrush *tempBrush = new ScatterBrush;
    propertiesWindow.NewBrush(tempBrush);
    propertiesWindow.ShowScatterControls();

    //execute the window, and check if it was accepted
    if(propertiesWindow.exec() == QDialog::Accepted)
    {
        //add the new brush to the list
        scatter.append(tempBrush);

        //and repopulate the lists
        RepopulateBrushLists();
    }
    //if it wasnts accepted
    else
    {
        //get rid of our new brush
        delete tempBrush;
    }
}

void BrushManager::on_scatterBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    scatterBrushIndex = index;

    if(scatterBrushIndex < scatter.count())
    {
        currentBrush = scatter[scatterBrushIndex];
        emit BrushChanged(currentBrush->GetCursor(), BrushManager::Scatter);
    }
    else
    {
        //they clicked the add brush option, so add one
        on_addScatterBrush_clicked();
    }
}

void BrushManager::on_editScatterBrush_clicked()
{
    if(ui->scatterBrushCombo->currentIndex() != -1)
    {
        propertiesWindow.EditBrush(scatter[scatterBrushIndex]);
        propertiesWindow.SetListIndex(0);
        propertiesWindow.exec();

        RepopulateBrushLists();
    }
}

void BrushManager::on_deleteScatterBrush_clicked()
{
    //if a brush is selected
    if(ui->scatterBrushCombo->currentIndex() != -1)
    {
        delete scatter[scatterBrushIndex];
        scatter.removeAt(scatterBrushIndex);

        RepopulateBrushLists();
    }
}

void BrushManager::on_smartBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    smartBrushIndex = index;

    if(smartBrushIndex < smart.count())
    {
        currentBrush = smart[smartBrushIndex];
        emit BrushChanged(currentBrush->GetCursor(), BrushManager::Smart);
    }
    else
    {
        on_addSmartBrush_clicked();
    }
}

void BrushManager::on_addSmartBrush_clicked()
{
    //create a new brush and pass it to the properties window
    SmartBrush *tempBrush = new SmartBrush;
    propertiesWindow.NewBrush(tempBrush);
    propertiesWindow.ShowSmartControls();

    //execute the window, and check if it was accepted
    if(propertiesWindow.exec() == QDialog::Accepted)
    {
        //add the new brush to the list
        smart.append(tempBrush);

        //and repopulate the lists
        RepopulateBrushLists();
    }
    //if it wasnts accepted
    else
    {
        //get rid of our new brush
        delete tempBrush;
    }
}

void BrushManager::on_editSmartBrushes_clicked()
{
    if(ui->smartBrushCombo->currentIndex() != -1)
    {
        propertiesWindow.EditBrush(smart[smartBrushIndex]);
        propertiesWindow.SetListIndex(4);
        propertiesWindow.exec();

        RepopulateBrushLists();
    }
}

void BrushManager::on_addReplacerBrush_clicked()
{
    //create a new brush and pass it to the properties window
    ReplacerBrush *tempBrush = new ReplacerBrush;
    propertiesWindow.NewBrush(tempBrush);
    propertiesWindow.ShowReplacerControls();

    //execute the window, and check if it was accepted
    if(propertiesWindow.exec() == QDialog::Accepted)
    {
        //add the new brush to the list
        replacer.append(tempBrush);

        //and repopulate the lists
        RepopulateBrushLists();
    }
    //if it wasnt accepted
    else
    {
        //get rid of our new brush
        delete tempBrush;
    }
}

void BrushManager::on_editReplacerBrush_clicked()
{
    if(ui->replacerBrushCombo->currentIndex() != -1)
    {
        propertiesWindow.EditBrush(replacer[replacerBrushIndex]);
        propertiesWindow.SetListIndex(0);
        propertiesWindow.exec();

        RepopulateBrushLists();
    }
}

void BrushManager::on_deleteReplacerBrush_clicked()
{
    //if a brush is selected
    if(ui->replacerBrushCombo->currentIndex() != -1)
    {
        delete replacer[replacerBrushIndex];
        replacer.removeAt(replacerBrushIndex);

        RepopulateBrushLists();
    }
}

void BrushManager::on_replacerBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    replacerBrushIndex = index;

    if(replacerBrushIndex < replacer.count())
    {
        currentBrush = replacer[replacerBrushIndex];
        emit BrushChanged(currentBrush->GetCursor(), BrushManager::Replacer);
    }
    else
    {
        on_addReplacerBrush_clicked();
    }
}

void BrushManager::on_addMatrixBrush_clicked()
{
    //create a new brush and pass it to the properties window
    MatrixBrush *tempBrush = new MatrixBrush;
    propertiesWindow.NewBrush(tempBrush);
    propertiesWindow.ShowMatrixControls();

    //execute the window, and check if it was accepted
    if(propertiesWindow.exec() == QDialog::Accepted)
    {
        //add the new brush to the list
        matrix.append(tempBrush);

        //and repopulate the lists
        RepopulateBrushLists();
    }
    //if it wasnt accepted
    else
    {
        //get rid of our new brush
        delete tempBrush;
    }
}

void BrushManager::on_editMatrixBrush_clicked()
{
    if(ui->matrixBrushCombo->currentIndex() != -1)
    {
        propertiesWindow.EditBrush(matrix[matrixBrushIndex]);
        propertiesWindow.SetListIndex(0);
        propertiesWindow.exec();

        RepopulateBrushLists();
    }
}

void BrushManager::on_deleteMatrixBrush_clicked()
{
    //if a brush is selected
    if(ui->matrixBrushCombo->currentIndex() != -1)
    {
        delete matrix[matrixBrushIndex];
        matrix.removeAt(matrixBrushIndex);

        RepopulateBrushLists();
    }
}

void BrushManager::on_matrixBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    matrixBrushIndex = index;

    if(matrixBrushIndex < matrix.count())
    {
        currentBrush = matrix[matrixBrushIndex];
        emit BrushChanged(currentBrush->GetCursor(), BrushManager::Matrix);
    }
    else
    {
        on_addMatrixBrush_clicked();
    }
}
