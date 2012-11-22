#include "levelproperties.h"
#include "ui_levelproperties.h"

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
