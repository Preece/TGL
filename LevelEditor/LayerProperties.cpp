#include "LayerProperties.h"
#include "ui_LayerProperties.h"

LayerProperties::LayerProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayerProperties)
{
    ui->setupUi(this);
}

LayerProperties::~LayerProperties()
{
    delete ui;
}
