#include "BrushPropertiesWidget.h"
#include "ui_BrushPropertiesWidget.h"

BrushPropertiesWidget::BrushPropertiesWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BrushPropertiesWidget)
{
    ui->setupUi(this);

    currentBrush = &pencil;
    propertiesWindow = NULL;

    ui->scatterBrushGroup->hide();
    ui->smartBrushGroup->hide();
}

BrushPropertiesWidget::~BrushPropertiesWidget()
{
    delete ui;

    if(propertiesWindow)
        delete propertiesWindow;
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
    //loop over the brush list and add them all
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
    //create the properties window if it has not already been done
    if(propertiesWindow == NULL)
    {
        propertiesWindow = new BrushPropertiesWindow;
        propertiesWindow->RegisterTileSelector();
    }

    //create a new brush and pass it to the properties window
    ScatterBrush *tempBrush = new ScatterBrush;
    propertiesWindow->NewScatterBrush(tempBrush);

    //execute the window, and check if it was accepted
    if(propertiesWindow->exec() == QDialog::Accepted)
    {
        //add the new brush to the list
        //and repopulate the lists
    }
    //if it wasnts accepted
    else
    {
        //get rid of our new brush
        delete tempBrush;
    }
}
