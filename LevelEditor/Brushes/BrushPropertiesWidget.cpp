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

    ui->scatterBrushGroup->hide();
    ui->smartBrushGroup->hide();

    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}

BrushPropertiesWidget::~BrushPropertiesWidget()
{
    delete ui;
}

void BrushPropertiesWidget::SetCurrentBrush(int type)
{
    ui->scatterBrushGroup->hide();
    ui->smartBrushGroup->hide();

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

    //scatter
    case 6:
        if(scatterBrushIndex < scatter.count())
        {
            currentBrush = scatter[scatterBrushIndex];
        }
        else
            currentBrush = NULL;

        ui->scatterBrushGroup->show();

        break;


    //scatter fill
    case 8:
    /*    if(scatterBrushIndex < scatter.count())
        {
            currentBrush = scatter[scatterBrushIndex];
        }
        else
            currentBrush = NULL;

        ui->scatterBrushGroup->show();
        break;*/

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
}

void BrushPropertiesWidget::SetSelectedTileID(int newID)
{
    pencil.SetSelectedTileID(newID);
    bucket.SetSelectedTileID(newID);
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
