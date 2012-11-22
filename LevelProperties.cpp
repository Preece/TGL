#include "LevelProperties.h"
#include "ui_LevelProperties.h"

LevelProperties::LevelProperties(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LevelProperties)
{
    ui->setupUi(this);
}

LevelProperties::~LevelProperties()
{
    delete ui;
}
