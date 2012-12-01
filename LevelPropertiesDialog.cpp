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

void LevelPropertiesDialog::on_mapNameInput_textChanged(const QString &arg1)
{
    if(resourceManager)
    {
        resourceManager->GetLevelProperties()->SetLevelName(arg1);
    }
}

void LevelPropertiesDialog::LoadValues()
{
    //put all the level properties values into the inputs
    ui->mapNameInput->setText(resourceManager->GetLevelProperties()->GetLevelname());

    ui->tileSizeX->setValue(resourceManager->GetLevelProperties()->GetTileWidth());
    ui->tileSizeY->setValue(resourceManager->GetLevelProperties()->GetTileHeight());
    ui->mapSizeX->setValue(resourceManager->GetLevelProperties()->GetMapWidth());
    ui->mapSizeY->setValue(resourceManager->GetLevelProperties()->GetMapHeight());
}

void LevelPropertiesDialog::on_tileSizeX_valueChanged(int arg1)
{
    if(resourceManager)
    {
        resourceManager->GetLevelProperties()->SetTileWidth(arg1);
    }
}

void LevelPropertiesDialog::on_tileSizeY_valueChanged(int arg1)
{
    if(resourceManager)
    {
        resourceManager->GetLevelProperties()->SetTileHeight(arg1);
    }
}

void LevelPropertiesDialog::on_mapSizeX_valueChanged(int arg1)
{
    if(resourceManager)
    {
        resourceManager->GetLevelProperties()->SetMapWidth(arg1);
    }
}

void LevelPropertiesDialog::on_mapSizeY_valueChanged(int arg1)
{
    if(resourceManager)
    {
        resourceManager->GetLevelProperties()->SetMapHeight(arg1);
    }
}
