#include "BrushPropertiesWindow.h"
#include "ui_BrushPropertiesWindow.h"

BrushPropertiesWindow::BrushPropertiesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BrushPropertiesWindow)
{
    ui->setupUi(this);

    resourceManager = NULL;
    currentScatterBrush = NULL;
    ui->tileList->setScene(&tileList);
}

BrushPropertiesWindow::~BrushPropertiesWindow()
{
    delete ui;
}

void BrushPropertiesWindow::RegisterTileSelector(QGraphicsScene *selector)
{
    ui->tileSelector->setScene(selector);
}

void BrushPropertiesWindow::NewScatterBrush(ScatterBrush *newBrush)
{
    tileList.clear();
    currentScatterBrush = newBrush;
}
