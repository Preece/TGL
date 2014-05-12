#include "LevelPropertiesDialog.h"
#include "ui_LevelPropertiesDialog.h"

LevelPropertiesDialog::LevelPropertiesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelPropertiesDialog)
{
    ui->setupUi(this);

    resourceController = NULL;
}

LevelPropertiesDialog::~LevelPropertiesDialog()
{
    delete ui;
}

void LevelPropertiesDialog::LoadValues()
{
    //put all the level properties values into the inputs
    ui->mapNameInput->setText(resourceController->GetLevelProperties()->GetLevelName());

    ui->tileSizeX->setValue(resourceController->GetTileWidth());
    ui->tileSizeY->setValue(resourceController->GetTileHeight());
    //ui->mapSizeX->setValue(resourceController->GetCurrentLayerWidth());
    //ui->mapSizeY->setValue(resourceController->GetCurrentLayerHeight());
}

void LevelPropertiesDialog::on_buttonBox_accepted()
{
    if(resourceController)
    {
        resourceController->GetLevelProperties()->SetLevelName(ui->mapNameInput->text());
        resourceController->GetLevelProperties()->SetTileSize(ui->tileSizeX->value(), ui->tileSizeY->value());
    }
}
