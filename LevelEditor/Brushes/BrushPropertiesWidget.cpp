#include "BrushPropertiesWidget.h"
#include "ui_BrushPropertiesWidget.h"

BrushPropertiesWidget::BrushPropertiesWidget(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::BrushPropertiesWidget)
{
    ui->setupUi(this);

    currentBrush = &pencil;
}

BrushPropertiesWidget::~BrushPropertiesWidget()
{
    delete ui;
}

void BrushPropertiesWidget::SetCurrentBrush(int type)
{
}

void BrushPropertiesWidget::on_pencilSizeInput_valueChanged(int arg1)
{
    //update the pencil size
    pencil.SetSize(arg1);
}

void BrushPropertiesWidget::SetSelectedTileID(int newID)
{
    pencil.SetSelectedTileID(newID);
}

void BrushPropertiesWidget::on_overwriteCheckbox_toggled(bool checked)
{
    pencil.SetOverwrite(checked);
}
