#include "objecteditor.h"
#include "ui_objecteditor.h"

ObjectEditor::ObjectEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectEditor)
{
    ui->setupUi(this);
}

ObjectEditor::~ObjectEditor()
{
    delete ui;
}
