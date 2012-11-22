#include "ResourceTab.h"
#include "ui_ResourceTab.h"

ResourceTab::ResourceTab(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ResourceTab)
{
    ui->setupUi(this);

    imageViewer = NULL;
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

    //loop through all the objects
        //add the object to the proper category
}

void ResourceTab::RepopulateSpriteSelector()
{
    //clear the sprite selector

    //loop through all of the sprites
    //add the sprite to the selector
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
