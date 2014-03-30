#include "SpritesheetSelector.h"
#include "ui_SpritesheetSelector.h"

SpritesheetSelector::SpritesheetSelector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpritesheetSelector)
{
    ui->setupUi(this);

    resourceManager = 0;
}

SpritesheetSelector::~SpritesheetSelector()
{
    delete ui;
}

void SpritesheetSelector::RepopulateImageList()
{
    //clear the image selector
    ClearImageList();

    if(!resourceManager)
        return;

    //loop through the images in the resource manager
    for(int i = 0; i < resourceManager->GetImageCount(); i++)
    {
        //assign the image from the RM to a new selector item
        ImageListWidgetItem *tempImageItem = new ImageListWidgetItem;
        tempImageItem->SetImage(resourceManager->GetImageByIndex(i));

        //add the selector item into the list
        ui->imageList->addItem(tempImageItem);
    }
}

Image *SpritesheetSelector::GetSelectedImage()
{
    //if nothing is selected, return a null value
    if(ui->imageList->currentRow() == -1)
        return NULL;

    //otherwise, retrieve the currently selected item
    return selectedImage;
}

bool SpritesheetSelector::IsImageSelected()
{
    if(ui->imageList->currentRow() == -1)
        return false;

    return true;
}

void SpritesheetSelector::ClearImageList()
{
    //for(int i = 0; i < ui->imageList->count(); i++)
    //{
    //    ui->imageList->takeItem(i);
    //}

    ui->imageList->clear();
}

void SpritesheetSelector::on_imageList_currentItemChanged(QListWidgetItem *current)
{
    if(IsImageSelected())
    {
        ImageListWidgetItem *tempItem = dynamic_cast<ImageListWidgetItem*>(current);
        selectedImage = tempItem->GetImage();
    }
    else
        selectedImage = NULL;
}
