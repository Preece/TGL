#include "ResourceTab.h"
#include "ui_ResourceTab.h"

ResourceTab::ResourceTab(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ResourceTab)
{
    ui->setupUi(this);

    imageViewer = NULL;
    spriteWindow = NULL;
    objectEditorWindow = NULL;

    connect(ui->addSpriteButton, SIGNAL(clicked()), this, SIGNAL(NewSpriteButtonClicked()));
    connect(ui->addObjectButton, SIGNAL(clicked()), this, SIGNAL(NewObjectButtonClicked()));

    //set up the tree view
    NPCTree = new QTreeWidgetItem(ui->objectSelector);
    NPCTree->setText(0, "NPCs");
    EnemyTree = new QTreeWidgetItem(ui->objectSelector);
    EnemyTree->setText(0, "Enemies");
    ItemTree = new QTreeWidgetItem(ui->objectSelector);
    ItemTree->setText(0, "Items");
    DoodadTree = new QTreeWidgetItem(ui->objectSelector);
    DoodadTree->setText(0, "Doodads");
}

ResourceTab::~ResourceTab()
{
    delete ui;
}

void ResourceTab::RepopulateTileSelector()
{
    //clear the tile selection panel
    //load the new tilesets into the selector
}

void ResourceTab::RepopulateObjectSelector()
{
    //clear the object selector
    qDeleteAll(NPCTree->takeChildren());
    qDeleteAll(EnemyTree->takeChildren());
    qDeleteAll(ItemTree->takeChildren());
    qDeleteAll(DoodadTree->takeChildren());

    ObjectSelectorItem *tempObject;

    //loop through all the objects
    for(int i = 0; i < resourceManager->GetObjectPrototypeCount(); i++)
    {
        //add the object to the proper category
        tempObject = new ObjectSelectorItem;
        tempObject->SetObject(resourceManager->GetObjectPrototypeByIndex(i));

        tempObject->setText(0, tempObject->GetObject()->GetObjectName());

        if(tempObject->GetObject()->GetType() == 0)
            NPCTree->addChild(tempObject);
        else if(tempObject->GetObject()->GetType() == 1)
            EnemyTree->addChild(tempObject);
        else if(tempObject->GetObject()->GetType() == 2)
            ItemTree->addChild(tempObject);
        else if(tempObject->GetObject()->GetType() == 3)
            DoodadTree->addChild(tempObject);
        else
            delete tempObject;
    }
}

void ResourceTab::RepopulateSpriteSelector()
{
    //clear the sprite selector
    ui->spriteSelector->clear();

    SpriteSelectorItem *tempItem;

    //loop through all of the sprites
    for(int i = 0; i < resourceManager->GetSpriteCount(); i++)
    {
        //create a new sprite selector item and add the sprite to it
        tempItem = new SpriteSelectorItem;
        tempItem->SetSprite(resourceManager->GetSpriteByIndex(i));

        //add the sprite to the selector
        ui->spriteSelector->addItem(tempItem);
    }
}

void ResourceTab::RepopulateImageSelector()
{
    //clear the image selector
    ui->imageSelector->clear();

    ImageSelectorItem *tempImageItem;

    //loop through the images in the resource manager
    for(int i = 0; i < resourceManager->GetImageCount(); i++)
    {
        //assign the image from the RM to a new selector item
        tempImageItem = new ImageSelectorItem;
        tempImageItem->SetImage(resourceManager->GetImageByIndex(i));

        //add the selector item into the list
        ui->imageSelector->addItem(tempImageItem);
    }

}

void ResourceTab::on_addImageButton_clicked()
{
    //create a new temporary image
    Image *tempImage;

    //ask the user where to load the file from.
    QString filename = QFileDialog::getOpenFileName(this, "Add Image", ".", "Portable Network Graphics (*.png)");

    //if the dialog succeeds
    if(!filename.isEmpty())
    {
        tempImage = new Image;

        //load the file
        tempImage->SetImageFromFile(filename);

        //add the image to the resource manager
        resourceManager->AddImage(tempImage);

        //repopulate the image selector
        RepopulateImageSelector();
    }
}

void ResourceTab::on_viewImageButton_clicked()
{
    //create the image viewer if it does not already exist
    if(imageViewer == NULL)
        imageViewer = new ImageViewer;

    if(IsImageSelected())
    {
        imageViewer->DisplayImage(GetSelectedImage());
        imageViewer->show();
        imageViewer->setFocus();
        imageViewer->raise();
    }
}

bool ResourceTab::IsImageSelected()
{
    //if an image is not selected
    if(ui->imageSelector->currentRow() == -1)
    {
        //warn the user that they must select an image

        return false;
    }

    return true;
}

ImageSelectorItem *ResourceTab::GetSelectedImageItem()
{
    if(IsImageSelected())
    {
        //retrieve the list item
        ImageSelectorItem *tempItem = dynamic_cast<ImageSelectorItem*>(ui->imageSelector->currentItem());

        //warn if the cast failed
        if(tempItem == 0)
            QMessageBox::warning(this, "Warning", "The dynamic cast has failed!");

        return tempItem;
    }

    return NULL;
}

Image *ResourceTab::GetSelectedImage()
{
    if(IsImageSelected())
        return GetSelectedImageItem()->GetImage();

    return NULL;
}

bool ResourceTab::IsSpriteSelected()
{
    if(ui->spriteSelector->currentRow() == -1)
        return false;

    return true;
}

SpriteSelectorItem *ResourceTab::GetSelectedSpriteItem()
{
    if(IsSpriteSelected())
    {
        //retrieve the list item
        SpriteSelectorItem *tempItem = dynamic_cast<SpriteSelectorItem*>(ui->spriteSelector->currentItem());

        //warn if the cast failed
        if(tempItem == 0)
            QMessageBox::warning(this, "Warning", "The dynamic cast has failed!");

        return tempItem;
    }

    return NULL;
}

Sprite *ResourceTab::GetSelectedSprite()
{
    if(IsSpriteSelected())
        return GetSelectedSpriteItem()->GetSprite();

    return NULL;
}

bool ResourceTab::IsObjectSelected()
{
    QTreeWidgetItem *item = ui->objectSelector->currentItem();
    if(item == NULL)
        return false;

    if(item == NPCTree || item == EnemyTree || item == ItemTree || item == DoodadTree)
        return false;

    return true;
}

ObjectSelectorItem *ResourceTab::GetSelectedObjectItem()
{
    if(IsObjectSelected())
    {
        //retrieve the list item
        ObjectSelectorItem *tempItem = dynamic_cast<ObjectSelectorItem*>(ui->objectSelector->currentItem());

        //warn if the cast failed
        if(tempItem == 0)
            QMessageBox::warning(this, "Warning", "The dynamic cast has failed!");

        return tempItem;
    }

    return NULL;
}

ObjectPrototype *ResourceTab::GetSelectedObject()
{
    if(IsObjectSelected())
    {
        return GetSelectedObjectItem()->GetObject();
    }

    return NULL;
}

void ResourceTab::on_deleteImageButton_clicked()
{
    //make sure an image is selected
    if(IsImageSelected())
    {
        //if so, tell the resource manager to delete the item by its ID
        resourceManager->DeleteImage(GetSelectedImage()->GetID());

        //and repopulate the image list
        RepopulateImageSelector();
    }
}

void ResourceTab::on_editSpriteButton_clicked()
{
    if(IsSpriteSelected())
    {
        //create the sprite editing window if it does not already exist
        if(!spriteWindow)
        {
            spriteWindow = new SpriteEditor;
            spriteWindow->RegisterResourceManager(resourceManager);
        }

        spriteWindow->EditSprite(GetSelectedSprite());

        spriteWindow->exec();

        RepopulateSpriteSelector();
    }
}

void ResourceTab::on_addSpriteButton_clicked()
{
    //create the sprite editing window if it does not already exist
    if(!spriteWindow)
    {
        spriteWindow = new SpriteEditor;
        spriteWindow->RegisterResourceManager(resourceManager);
    }

    //create a temporary sprite for the dialog to operate upon
    Sprite *temporarySprite = new Sprite;

    //pass the temporary sprite to the dialog
    spriteWindow->NewSprite(temporarySprite);

    //add the sprite to the resource manager if the dialog is accepted
    if(spriteWindow->exec() == QDialog::Accepted)
    {
        resourceManager->AddSprite(temporarySprite);
        RepopulateSpriteSelector();
    }
    //delete the temporary sprite if the dialog is rejected
    else
    {
        delete temporarySprite;
    }
}

void ResourceTab::on_addObjectButton_clicked()
{
    if(!objectEditorWindow)
    {
        objectEditorWindow = new ObjectEditor;
        objectEditorWindow->RegisterResourceManager(resourceManager);
    }

    ObjectPrototype *tempObject = new ObjectPrototype;
    objectEditorWindow->NewObject(tempObject);

    if(objectEditorWindow->exec() == QDialog::Accepted)
    {
        resourceManager->AddObjectPrototype(tempObject);
        RepopulateObjectSelector();
    }
    else
    {
        delete tempObject;
    }
}

void ResourceTab::on_editObjectButton_clicked()
{
    if(IsObjectSelected())
    {
        //create the sprite editing window if it does not already exist
        if(!objectEditorWindow)
        {
            objectEditorWindow = new ObjectEditor;
            objectEditorWindow->RegisterResourceManager(resourceManager);
        }

        objectEditorWindow->EditObject(GetSelectedObject());

        objectEditorWindow->exec();

        RepopulateObjectSelector();
    }
}

void ResourceTab::on_selectTilesetButton_clicked()
{
    //bring up an image selection window
}
