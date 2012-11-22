#include "ObjectEditor.h"
#include "ui_ObjectEditor.h"

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
