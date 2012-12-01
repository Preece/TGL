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

    ui->tileSizeX->setValue(resourceManager->GetLevelProperties()->GetTileWidth());
    ui->tileSizeY->setValue(resourceManager->GetLevelProperties()->GetTileHeight());
    ui->mapSizeX->setValue(resourceManager->GetLevelProperties()->GetMapWidth());
    ui->mapSizeY->setValue(resourceManager->GetLevelProperties()->GetMapHeight());
}

void LevelPropertiesDialog::on_buttonBox_accepted()
{
    if(resourceManager)
    {
        resourceManager->GetLevelProperties()->SetLevelName(ui->mapNameInput->text());
        resourceManager->GetLevelProperties()->SetTileWidth(ui->tileSizeX->value());
        resourceManager->GetLevelProperties()->SetTileHeight(ui->tileSizeY->value());
        resourceManager->GetLevelProperties()->SetMapWidth(ui->mapSizeX->value());
        resourceManager->GetLevelProperties()->SetMapHeight(ui->mapSizeY->value());
    }
}
