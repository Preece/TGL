#include "ResourceTab.h"
#include "ui_ResourceTab.h"

ResourceTab::ResourceTab(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::ResourceTab)
{
    ui->setupUi(this);

    imageViewer = NULL;
    spriteWindow = NULL;
    tileSelector = NULL;
    spritesheet = NULL;

    connect(ui->addSpriteButton, SIGNAL(clicked()), this, SIGNAL(NewSpriteButtonClicked()));
}

ResourceTab::~ResourceTab()
{
    delete ui;

    if(spriteWindow)
        delete spriteWindow;
}

void ResourceTab::RegisterTileSelector(TileSelectorScene *tiles)
{
    tileSelector = tiles;
    ui->tileSelector->setScene(tiles);
}

void ResourceTab::RepopulateTileSelector()
{
    //clear out all the items in the tile selector
    if(tileSelector)
        tileSelector->clear();
    else
        return;

    if(!spritesheet)
        return;

    if(!spritesheet->isNull())
    {
        int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
        int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

        if(tileW && tileH)
        {
            int imageW = spritesheet->width() / tileW;
            int imageH = spritesheet->height() / tileH;

            TileWidgetItem *tempItem;
            Tile *tempTile;

            //loop for the width of the spritesheet divided by the width of a tile
            for(int i = 0; i < imageH; i++)
            {
                //loop for the height of the spritesheet divided by the height of a tile
                for(int j = 0; j < imageW; j++)
                {
                    tempItem = new TileWidgetItem;

                    //copy the correct fragment of the image into a new TileItem
                    tempItem->SetTilePixmap(resourceManager->GetTilePixmap(i, j));

                    //create a tile with the correct origin points, and add it in
                    //the x and y and -1 to indicate that this doesnt exist in the tile
                    //grid, only in the selector pane
                    tempTile = new Tile();
                    tempTile->originX = i;
                    tempTile->originY = j;
                    tempTile->x = -1;
                    tempTile->y = -1;
                    tempItem->SetTile(tempTile);

                    //add the tile item to the tile selector at (i * tilewidth) + i
                    tileSelector->addItem(tempItem);

                    tempItem->setPos((j * tileW) + j, (i * tileH) + i);
                    tempItem->setFlag(QGraphicsItem::ItemIsSelectable);
                }
            }
        }
    }
}

void ResourceTab::RepopulateSpriteSelector()
{
    //clear the sprite selector
    ui->spriteSelector->clear();

    SpriteListWidgetItem *tempItem;

    //loop through all of the sprites
    for(int i = 0; i < resourceManager->GetSpriteCount(); i++)
    {
        //create a new sprite selector item and add the sprite to it
        tempItem = new SpriteListWidgetItem;
        tempItem->SetSprite(resourceManager->GetSpriteByIndex(i));

        //add the sprite to the selector
        ui->spriteSelector->addItem(tempItem);
    }
}

void ResourceTab::RepopulateImageSelector()
{
    //clear the image selector
    ui->imageSelector->clear();

    ImageListWidgetItem *tempImageItem;

    //loop through the images in the resource manager
    for(int i = 0; i < resourceManager->GetImageCount(); i++)
    {
        //assign the image from the RM to a new selector item
        tempImageItem = new ImageListWidgetItem;
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

ImageListWidgetItem *ResourceTab::GetSelectedImageItem()
{
    if(IsImageSelected())
    {
        //retrieve the list item
        ImageListWidgetItem *tempItem = dynamic_cast<ImageListWidgetItem*>(ui->imageSelector->currentItem());

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

SpriteListWidgetItem *ResourceTab::GetSelectedSpriteItem()
{
    if(IsSpriteSelected())
    {
        //retrieve the list item
        SpriteListWidgetItem *tempItem = dynamic_cast<SpriteListWidgetItem*>(ui->spriteSelector->currentItem());

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

void ResourceTab::on_selectTilesetButton_clicked()
{
    //bring up an image selection window
    SpritesheetSelector spritesheetWindow;

    spritesheetWindow.RegisterResourceManager(resourceManager);
    spritesheetWindow.RepopulateImageList();

    //if the user completes the dialog
    if(spritesheetWindow.exec() == QDialog::Accepted)
    {
        //and if an image was selected
        if(spritesheetWindow.IsImageSelected() && resourceManager->GetLevelProperties()->IsPropertiesSet())
        {
            //set the spritesheet as that image
            spritesheet = spritesheetWindow.GetSelectedImage()->GetImage();

            //store its ID as the image to be used as the tileset
            resourceManager->GetLevelProperties()->SetTilesetID(spritesheetWindow.GetSelectedImage()->GetID());

            //and repopulate the tile selector
            RepopulateTileSelector();
        }
    }
}

void ResourceTab::on_deleteSpriteButton_clicked()
{
    if(IsSpriteSelected())
    {
        resourceManager->DeleteSprite(GetSelectedSprite()->GetID());
        RepopulateSpriteSelector();
    }
}
