#include "BrushPropertiesWidget.h"
#include "ui_BrushPropertiesWidget.h"

BrushPropertiesWidget::BrushPropertiesWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BrushPropertiesWidget)
{
    ui->setupUi(this);

    currentBrush = &pencil;
    scatterBrushIndex = 0;

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

    //smart
    case 7:
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
    propertiesWindow.NewScatterBrush(tempBrush);

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
        propertiesWindow.EditScatterBrush(scatter[scatterBrushIndex]);

        propertiesWindow.exec();

        RepopulateBrushLists();
    }
}
