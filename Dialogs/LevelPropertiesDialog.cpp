#include "LevelPropertiesDialog.h"
#include "ui_LevelPropertiesDialog.h"

LevelPropertiesDialog::LevelPropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelPropertiesDialog)
{
    ui->setupUi(this);

    resourceManager = NULL;
}

LevelPropertiesDialog::~LevelPropertiesDialog()
{
    delete ui;
}

void LevelPropertiesDialog::LoadValues()
{
    //put all the level properties values into the inputs
    ui->mapNameInput->setText(resourceManager->GetLevelProperties()->GetLevelName());

    ui->tileSizeX->setValue(resourceManager->GetTileWidth());
    ui->tileSizeY->setValue(resourceManager->GetTileHeight());
    ui->mapSizeX->setValue(resourceManager->GetCurrentLayerWidth());
    ui->mapSizeY->setValue(resourceManager->GetCurrentLayerHeight());
}

void LevelPropertiesDialog::on_buttonBox_accepted()
{
    if(resourceManager)
    {
        resourceManager->GetLevelProperties()->SetLevelName(ui->mapNameInput->text());
        resourceManager->GetLevelProperties()->SetTileSize(ui->tileSizeX->value(), ui->tileSizeY->value());
    }
}
