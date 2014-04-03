#include "BrushPropertiesWidget.h"
#include "ui_BrushPropertiesWidget.h"

BrushPropertiesWidget::BrushPropertiesWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BrushPropertiesWidget)
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
}

BrushPropertiesWidget::~BrushPropertiesWidget()
{
    delete ui;

    DestroyBrushes();
}

//high is 11
void BrushPropertiesWidget::SetCurrentBrush(int type)
{
    ui->scatterBrushGroup->hide();
    ui->smartBrushGroup->hide();
    ui->replacerGroup->hide();
    ui->matrixBrushGroup->hide();

    switch(type)
    {
    //pencil
    case 0:
        currentBrush = &pencil;
        break;

    //bucket
    case 2:
        currentBrush = &bucket;
        break;

    //eraser
    case 3:
        currentBrush = &eraser;
        break;

    //line
    case 10:
        currentBrush = &line;
        break;
        
    //stamp
    case 12:
        currentBrush = &stamp;
        break;

    //scatter
    case 6:
        if(scatterBrushIndex < scatter.count())
        {
            scatter[scatterBrushIndex]->SetFill(false);
            currentBrush = scatter[scatterBrushIndex];
        }
        else
            currentBrush = NULL;

        ui->scatterBrushGroup->show();

        break;

    //smart
    case 7:
        if(smartBrushIndex < smart.count())
        {
            currentBrush = smart[smartBrushIndex];
        }
        else
            currentBrush = NULL;

        ui->smartBrushGroup->show();
        break;

    //scatter fill
    case 8:
        if(scatterBrushIndex < scatter.count())
        {
            scatter[scatterBrushIndex]->SetFill(true);
            currentBrush = scatter[scatterBrushIndex];

        }
        else
            currentBrush = NULL;

        ui->scatterBrushGroup->show();
        break;

    //replacer brush
    case 9:
        if(replacerBrushIndex < replacer.count())
        {
            currentBrush = replacer[replacerBrushIndex];

        }
        else
            currentBrush = NULL;

        ui->replacerGroup->show();
        break;

    //matrix brush
    case 11:
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
}

void BrushPropertiesWidget::RepopulateBrushLists()
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

    ui->smartBrushCombo->clear();

    for(int i = 0; i < smart.count(); i++)
    {
        ui->smartBrushCombo->addItem(smart[i]->GetName());
        ui->smartBrushCombo->setCurrentIndex(i);
        smartBrushIndex = i;
    }

    ui->replacerBrushCombo->clear();

    for(int i = 0; i < replacer.count(); i++)
    {
        ui->replacerBrushCombo->addItem(replacer[i]->GetName());
        ui->replacerBrushCombo->setCurrentIndex(i);
        replacerBrushIndex = i;
    }

    ui->matrixBrushCombo->clear();

    for(int i = 0; i < matrix.count(); i++)
    {
        ui->matrixBrushCombo->addItem(matrix[i]->GetName());
        ui->matrixBrushCombo->setCurrentIndex(i);
        matrixBrushIndex = i;
    }
}

void BrushPropertiesWidget::DestroyBrushes()
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

void BrushPropertiesWidget::SetSelectedTiles(TileList newList)
{
    if(newList.count() > 0)
    {
        pencil.SetSelectedTileOrigin(newList[0]);
        bucket.SetSelectedTileOrigin(newList[0]);
    }

    stamp.CreateGrid(newList);
}

void BrushPropertiesWidget::on_overwriteCheckbox_toggled(bool checked)
{
    pencil.SetOverwrite(checked);
}

void BrushPropertiesWidget::on_brushSizeInput_valueChanged(int arg1)
{
    pencil.SetSize(arg1);
    eraser.SetSize(arg1);
}

void BrushPropertiesWidget::on_addScatterBrush_clicked()
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

void BrushPropertiesWidget::on_scatterBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    scatterBrushIndex = index;

    if(scatterBrushIndex < scatter.count())
    {
        currentBrush = scatter[scatterBrushIndex];
        emit BrushChanged();
    }
}

void BrushPropertiesWidget::on_editScatterBrush_clicked()
{
    if(ui->scatterBrushCombo->currentIndex() != -1)
    {
        propertiesWindow.EditBrush(scatter[scatterBrushIndex]);
        propertiesWindow.SetListIndex(0);
        propertiesWindow.exec();

        RepopulateBrushLists();
    }
}

void BrushPropertiesWidget::on_deleteScatterBrush_clicked()
{
    //if a brush is selected
    if(ui->scatterBrushCombo->currentIndex() != -1)
    {
        delete scatter[scatterBrushIndex];
        scatter.removeAt(scatterBrushIndex);

        RepopulateBrushLists();
    }
}

void BrushPropertiesWidget::on_smartBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    smartBrushIndex = index;

    if(smartBrushIndex < smart.count())
    {
        currentBrush = smart[smartBrushIndex];
        emit BrushChanged();
    }
}

void BrushPropertiesWidget::on_addSmartBrush_clicked()
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

void BrushPropertiesWidget::on_editSmartBrushes_clicked()
{
    if(ui->smartBrushCombo->currentIndex() != -1)
    {
        propertiesWindow.EditBrush(smart[smartBrushIndex]);
        propertiesWindow.SetListIndex(4);
        propertiesWindow.exec();

        RepopulateBrushLists();
    }
}

void BrushPropertiesWidget::on_addReplacerBrush_clicked()
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

void BrushPropertiesWidget::on_editReplacerBrush_clicked()
{
    if(ui->replacerBrushCombo->currentIndex() != -1)
    {
        propertiesWindow.EditBrush(replacer[replacerBrushIndex]);
        propertiesWindow.SetListIndex(0);
        propertiesWindow.exec();

        RepopulateBrushLists();
    }
}

void BrushPropertiesWidget::on_deleteReplacerBrush_clicked()
{
    //if a brush is selected
    if(ui->replacerBrushCombo->currentIndex() != -1)
    {
        delete replacer[replacerBrushIndex];
        replacer.removeAt(replacerBrushIndex);

        RepopulateBrushLists();
    }
}

void BrushPropertiesWidget::on_replacerBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    replacerBrushIndex = index;

    if(replacerBrushIndex < replacer.count())
    {
        currentBrush = replacer[replacerBrushIndex];
        emit BrushChanged();
    }
}

void BrushPropertiesWidget::on_addMatrixBrush_clicked()
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

void BrushPropertiesWidget::on_editMatrixBrush_clicked()
{
    if(ui->matrixBrushCombo->currentIndex() != -1)
    {
        propertiesWindow.EditBrush(matrix[matrixBrushIndex]);
        propertiesWindow.SetListIndex(0);
        propertiesWindow.exec();

        RepopulateBrushLists();
    }
}

void BrushPropertiesWidget::on_deleteMatrixBrush_clicked()
{
    //if a brush is selected
    if(ui->matrixBrushCombo->currentIndex() != -1)
    {
        delete matrix[matrixBrushIndex];
        matrix.removeAt(matrixBrushIndex);

        RepopulateBrushLists();
    }
}

void BrushPropertiesWidget::on_matrixBrushCombo_currentIndexChanged(int index)
{
    if(index == -1)
        return;

    matrixBrushIndex = index;

    if(matrixBrushIndex < matrix.count())
    {
        currentBrush = matrix[matrixBrushIndex];
        emit BrushChanged();
    }
}
