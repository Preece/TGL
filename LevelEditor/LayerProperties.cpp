#include "LayerProperties.h"
#include "ui_LayerProperties.h"

LayerProperties::LayerProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayerProperties)
{
    ui->setupUi(this);

    currentLayer = NULL;
}

LayerProperties::~LayerProperties()
{
    delete ui;
}

void LayerProperties::NewLayer(Layer *newLayer)
{
    currentLayer = newLayer;

    //set all the values to the default
    ui->layerNameInput->setText("");
    ui->opacitySlider->setValue(100);
    ui->verticalPValue->setValue(1.00);
    ui->horizontalPValue->setValue(1.00);
}

void LayerProperties::EditLayer(Layer *newLayer)
{
    currentLayer = newLayer;

    if(newLayer)
    {
        //set all the values to the layers
        ui->layerNameInput->setText(currentLayer->GetName());
        ui->opacitySlider->setValue(currentLayer->GetOpacity());
        ui->verticalPValue->setValue(currentLayer->GetVerticalParallax());
        ui->horizontalPValue->setValue(currentLayer->GetHorizontalParallax());
    }
}

void LayerProperties::on_buttonBox_accepted()
{
    if(currentLayer)
    {
        currentLayer->SetName(ui->layerNameInput->text());
        currentLayer->SetOpacity(ui->opacitySlider->value());
        currentLayer->SetHorizontalParallax(ui->horizontalPValue->value());
        currentLayer->SetVerticalParallax(ui->verticalPValue->value());
    }
}
