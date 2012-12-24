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
    ui->customValues->clear();

    RepopulateSpriteList();
    UpdateSymbol();
}

void ObjectEditor::EditObject(ObjectPrototype *newObject)
{
    if(newObject == NULL)
        return;

    currentObject = newObject;

    ui->objectNameInput->setText(newObject->GetObjectName());
    ui->objectTypeSelector->setCurrentIndex(newObject->GetObjectType());

    RepopulateSpriteList();
    RepopulateCustomValueList();
    UpdateSymbol();
}

void ObjectEditor::on_objectNameInput_textChanged(const QString &arg1)
{
    if(currentObject)
        currentObject->SetObjectName(arg1);
}

void ObjectEditor::on_objectTypeSelector_currentIndexChanged(int index)
{
    if(currentObject)
        currentObject->SetObjectType(index);
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

    UpdateSymbol();
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

void ObjectEditor::RepopulateCustomValueList()
{
    //clear the custom values list
    ui->customValues->clear();

    QMap<QString, QVariant> iter = currentObject->GetCustomValues();
    QTreeWidgetItem *tempItem;

    //loop through for every custom value in the object
    foreach (const QString &str, iter.keys())
    {
        //create the item
         tempItem = new QTreeWidgetItem(ui->customValues);

        //set the text of the item
        tempItem->setText(0, str);
        tempItem->setText(1, iter.value(str).toString());
    }
}

void ObjectEditor::UpdateSymbol()
{
    if(currentObject)
        ui->symbolPreview->setPixmap(resourceManager->GetSpriteSymbol(currentObject->GetSpriteID()));
}

void ObjectEditor::on_addCustomButton_clicked()
{
    QTreeWidgetItem *newItem = new QTreeWidgetItem(ui->customValues);
    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
    newItem->setText(0, "Name");
    newItem->setText(1, "Value");

}

void ObjectEditor::on_removeCustomButton_clicked()
{
    if(ui->customValues->currentItem() != NULL)
        delete ui->customValues->currentItem();
}

void ObjectEditor::on_customValues_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    ui->customValues->editItem(item, column);
}

void ObjectEditor::on_buttonBox_accepted()
{
    if(ui->objectNameInput->text() == "")
        currentObject->SetObjectName("New Object");

    //clear the objects custom value list
    currentObject->ClearCustomValues();

    QTreeWidgetItem *tempItem;
    QVariant tempValue;

    //loop through for every entry in the custom values tree
    for(int i = 0; i < ui->customValues->topLevelItemCount(); i++)
    {
        tempItem = ui->customValues->topLevelItem(i);

        tempValue = tempItem->text(1);

        //add the key/value pair
        currentObject->AddCustomValue(tempItem->text(0), tempValue);
    }

    currentObject = NULL;
}
