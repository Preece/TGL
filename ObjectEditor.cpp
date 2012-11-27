#include "ObjectEditor.h"
#include "ui_ObjectEditor.h"

ObjectEditor::ObjectEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ObjectEditor)
{
    ui->setupUi(this);

    currentObject = NULL;
}

ObjectEditor::~ObjectEditor()
{
    delete ui;
}

void ObjectEditor::NewObject(ObjectPrototype *newObject)
{
    currentObject = newObject;

    ui->objectNameInput->setText("");
    ui->objectTypeSelector->setCurrentIndex(0);
    ui->objectBehaviorSelector->setCurrentIndex(0);

    RepopulateSpriteList();
}

void ObjectEditor::EditObject(ObjectPrototype *newObject)
{
    if(newObject == NULL)
        return;

    ui->objectNameInput->setText(newObject->GetObjectName());
    ui->objectTypeSelector->setCurrentIndex(newObject->GetType());
    ui->objectBehaviorSelector->setCurrentIndex(newObject->GetBehavior());


    currentObject = newObject;

    RepopulateSpriteList();
}

void ObjectEditor::on_objectNameInput_textChanged(const QString &arg1)
{
    if(currentObject)
        currentObject->SetObjectName(arg1);
}

void ObjectEditor::on_objectTypeSelector_currentIndexChanged(int index)
{
    if(currentObject)
        currentObject->SetType(index);
}

void ObjectEditor::on_objectBehaviorSelector_currentIndexChanged(int index)
{
    if(currentObject)
        currentObject->SetBehavior(index);
}

void ObjectEditor::on_spriteList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    //abort of there is no item selected
    if(ui->spriteList->currentRow() == -1)
        return;

    //get the id from the selected item
    SpriteSelectorItem *tempItem = dynamic_cast<SpriteSelectorItem*>(current);

    //set the spriteID
    currentObject->AttachSprite(tempItem->GetSprite()->GetID());
}

void ObjectEditor::RepopulateSpriteList()
{
    ui->spriteList->clear();

    SpriteSelectorItem *tempItem;

    for(int i = 0; i < resourceManager->GetSpriteCount(); i++)
    {
        tempItem = new SpriteSelectorItem;
        tempItem->SetSprite(resourceManager->GetSpriteByIndex(i));

        tempItem->setText(tempItem->GetSprite()->GetName());
        ui->spriteList->addItem(tempItem);

        if(tempItem->GetSprite()->GetID() == currentObject->GetID())
            ui->spriteList->setCurrentItem(tempItem);
    }
}

void ObjectEditor::on_ObjectEditor_accepted()
{
    if(ui->objectNameInput->text() == "")
        currentObject->SetObjectName("New Object");
}
