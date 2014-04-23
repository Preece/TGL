#include "LayerPropertiesDialog.h"
#include "ui_LayerPropertiesDialog.h"

LayerPropertiesDialog::LayerPropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LayerPropertiesDialog)
{
    ui->setupUi(this);

    currentLayer = NULL;
}

LayerPropertiesDialog::~LayerPropertiesDialog()
{
    delete ui;
}

int LayerPropertiesDialog::SetupNewLayer(TileLayer *newLayer)
{
    currentLayer = newLayer;

    //set all the values to the default
    ui->layerNameInput->setText("");
    ui->opacitySlider->setValue(100);
    ui->verticalPValue->setValue(1.00);
    ui->horizontalPValue->setValue(1.00);

    return exec();
}

int LayerPropertiesDialog::EditLayer(TileLayer *newLayer)
{
    currentLayer = newLayer;

    if(currentLayer)
    {
        //set all the values to the layers
        ui->layerNameInput->setText(currentLayer->GetName());
        ui->opacitySlider->setValue(currentLayer->GetOpacity());
        ui->verticalPValue->setValue(currentLayer->GetVerticalParallax());
        ui->horizontalPValue->setValue(currentLayer->GetHorizontalParallax());

        return exec();
    }

    return 0;
}

void LayerPropertiesDialog::on_buttonBox_accepted()
{
    if(currentLayer)
    {
        if(ui->layerNameInput->text() == "")
            currentLayer->SetName("New Layer");
        else
            currentLayer->SetName(ui->layerNameInput->text());

        currentLayer->SetOpacity(ui->opacitySlider->value());
        currentLayer->SetHorizontalParallax(ui->horizontalPValue->value());
        currentLayer->SetVerticalParallax(ui->verticalPValue->value());
    }
}
