#include "SpriteEditor.h"
#include "ui_SpriteEditor.h"

SpriteEditor::SpriteEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpriteEditor)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowMaximizeButtonHint);

    zoomLevel = 1;
    animationEditor = 0;
    spritesheetSelector = 0;
    animationPreviewer = 0;
    spritesheetLoaded = false;

    //assign the screen to the view
    ui->imageView->setScene(&imageScene);
    imageItem = new QGraphicsPixmapItem();
    imageScene.addItem(imageItem);

    connect(&imageScene, SIGNAL(SelectionUpdated(QRect)), this, SLOT(StoreNewFrameRect(QRect)));
    connect(&imageScene, SIGNAL(RenderSpotUpdated(QPoint)), this, SLOT(StoreNewRenderSpot(QPoint)));

    //set up the tool buttons IDs
    ui->toolButtons->setId(ui->frameSelectTool, FRAME_SELECT_TOOL);
    ui->toolButtons->setId(ui->autoFrameSelectTool, AUTO_FRAME_SELECT_TOOL);
    ui->toolButtons->setId(ui->pointerTool, POINTER_TOOL);
    ui->toolButtons->setId(ui->renderSpotTool, RENDER_SPOT_TOOL);
    ui->toolButtons->setId(ui->addHotspotTool, HOTSPOT_TOOL);

    connect(ui->toolButtons, SIGNAL(buttonClicked(int)), this, SLOT(UpdateToolSelection(int)));
}

SpriteEditor::~SpriteEditor()
{
    delete ui;
}


void SpriteEditor::ClearAll()
{
    //clear all input from the sprite edit window
    ui->spriteNameInput->setText("");
    ui->animationList->clear();
    ui->frameList->clear();

    imageItem->hide();
}


///////////////////////////////ANIMATION FUNCTIONS////////////////////////////////////////////
bool SpriteEditor::IsAnimationSelected()
{
    //check if there is anything selected
    if(ui->animationList->currentRow() == -1)
        return false;

    return true;
}

AnimationListItem *SpriteEditor::GetSelectedAnimationItem()
{
    if(IsAnimationSelected())
    {
        //retrieve the list item
        AnimationListItem *tempItem = dynamic_cast<AnimationListItem*>(ui->animationList->currentItem());

        //warn if the cast failed
        QMessageBox warning;
        if(tempItem == 0)
            warning.warning(this, "Warning", "The dynamic cast has failed!");

        return tempItem;
    }

    return NULL;
}

Animation *SpriteEditor::GetSelectedAnimation()
{
    if(IsAnimationSelected())
        return GetSelectedAnimationItem()->GetAnimation();

    return NULL;
}

/////////////////////////////////FRAME FUNCTIONS//////////////////////////////////////////////
bool SpriteEditor::IsFrameSelected()
{
    if(ui->frameList->currentRow() == -1)
    {
        return false;
    }

    return true;
}

FrameListItem *SpriteEditor::GetSelectedFrameItem()
{
    if(IsAnimationSelected() && IsFrameSelected())
    {
        FrameListItem *tempFrameItem = dynamic_cast<FrameListItem*>(ui->frameList->currentItem());

        return tempFrameItem;
    }

    return NULL;
}

Frame *SpriteEditor::GetSelectedFrame()
{
    if(IsFrameSelected())
        return GetSelectedFrameItem()->GetFrame();

    return NULL;
}

void SpriteEditor::SetFrameIcon(FrameListItem *frameListItem)
{
    //check if a spritesheet has been loaded and frame data exists
    if(IsSpritesheetLoaded() && !frameListItem->GetFrame()->GetFrameRect().isNull())
    {
        //create an image from the selected frame data and the spritesheet
        QImage frameIcon;
        frameIcon = *(resourceManager->GetImage(currentSprite->GetImageID())->GetImage());
        frameIcon = frameIcon.copy(frameListItem->GetFrame()->GetFrameRect());

        //set the selected frames icon
        frameListItem->SetIcon(&frameIcon);
    }
    //if not, set the missing file icon
    else
    {
        frameListItem->SetIcon(NULL);
    }
}

void SpriteEditor::ClearFrameList()
{
    ui->frameList->clear();
}

void SpriteEditor::RepopulateFrameList()
{
    //clear out the frame list
    ClearFrameList();

    //if an animation is selected
    if(IsAnimationSelected())
    {
        FrameListItem *newFrameListItem;

        //loop through the frames of the selected animation
        for(int i = 0; i < GetSelectedAnimation()->GetFrameCount(); i++)
        {
            //create a frame list item
            newFrameListItem = new FrameListItem;

            //attach the frame at the current loop index
            newFrameListItem->SetFrame(GetSelectedAnimation()->GetFrameAtIndex(i));

            //update the frames icon
            SetFrameIcon(newFrameListItem);

            //add the frame list item to the listwidget
            ui->frameList->addItem(newFrameListItem);
            ui->frameList->setCurrentItem(newFrameListItem);
        }
    }
}

void SpriteEditor::StoreNewFrameRect(QRect newRect)
{
    //if a frame is selected
    if(IsFrameSelected())
    {
        //set the frame rect of the currently selected frame to the parameter
        GetSelectedFrame()->SetFrameRect(newRect);

        //update the frame items icon
        SetFrameIcon(GetSelectedFrameItem());
    }

    RepopulateFrameList();
}

void SpriteEditor::StoreNewRenderSpot(QPoint newSpot)
{
    if(IsFrameSelected())
    {
        GetSelectedFrame()->SetRenderSpot(newSpot);
    }
}

/////////////////////////////////IMAGE FUNCTIONS//////////////////////////////////////////////
void SpriteEditor::UpdateDisplayImage()
{
    //hide the image item until is has been proven to exist
    imageItem->hide();

    //get the image from the resource manager
    Image *tempImage = resourceManager->GetImage(currentSprite->GetImageID());

    //abort if the image doesn't exist
    if(tempImage == NULL)
        return;

    //abort of the image has no associated QImage loaded
    if(tempImage->GetImage()->isNull())
        return;

    imageItem->setPixmap(QPixmap::fromImage(*(resourceManager->GetImage(currentSprite->GetImageID())->GetImage())));
    imageItem->show();

    //notify the scene about the spritesheet
    imageScene.SetSpritesheet(imageItem->pixmap().toImage());

    //resize the scene
    imageScene.setSceneRect(imageItem->boundingRect());
}

void SpriteEditor::UpdateToolSelection(int newTool)
{
    ChangeTool(newTool);
}

void SpriteEditor::ChangeTool(int newTool)
{
    //change the current tool
    currentTool = newTool;

    //notify the scene about the change
    imageScene.SetTool(newTool);

    //change the cursor
    QCursor newCursor;

    switch(currentTool)
    {
    case RENDER_SPOT_TOOL:
    case HOTSPOT_TOOL:
    case FRAME_SELECT_TOOL:
        newCursor.setShape(Qt::CrossCursor);
        break;

    case POINTER_TOOL:
        newCursor.setShape(Qt::PointingHandCursor);
        break;

    case ZOOM_TOOL:
        break;
    }

    ui->imageView->setCursor(newCursor);
}

void SpriteEditor::NewSprite(Sprite *newSprite)
{
    ClearAll();

    //assign the working sprite pointer to the new sprite pointer provided
    currentSprite = newSprite;
}

void SpriteEditor::EditSprite(Sprite *editSprite)
{
    //assign the working sprite pointer to the pointer to be edited
    currentSprite = editSprite;

    //put the sprites name in the name input
    ui->spriteNameInput->setText(currentSprite->GetName());

    //load the image and put it into the graphics view
    UpdateDisplayImage();

    //loop through all the animations and fill the animation list
    AnimationListItem *tempItem;

    ui->animationList->clear();

    for(int i = 0; i < currentSprite->GetAnimationCount(); i++)
    {
        tempItem = new AnimationListItem;
        tempItem->SetAnimation(currentSprite->GetAnimationByIndex(i));

        ui->animationList->addItem(tempItem);
    }


}


void SpriteEditor::on_buttonBox_accepted()
{
    //check that the name is filled out
    if(ui->spriteNameInput->text() == "")
    {
        currentSprite->SetName("New Sprite");
    }
    else
        currentSprite->SetName(ui->spriteNameInput->text());

    //clear the reference to the working sprite
    currentSprite = NULL;

}

void SpriteEditor::on_addAnimationButton_clicked()
{
    //create the editor dialog if it does not already exist
    if(animationEditor == 0)
    {
        animationEditor = new AnimationEditor;
    }

    //create a temporary animation for the animation editor to work on
    Animation *temporaryAnimation = new Animation;

    //notify the animation editor about the temporary animation
    animationEditor->NewAnimation(temporaryAnimation);

    //run the dialog, and fill in the values if accepted
    if(animationEditor->exec() == QDialog::Accepted)
    {
        //create an animation list item
        AnimationListItem *tempAnimationListItem = new AnimationListItem;

        //attach the new animation to the list item
        tempAnimationListItem->SetAnimation(temporaryAnimation);

        //add the animation list item into the listbox
        ui->animationList->addItem(tempAnimationListItem);
        //select the new item
        ui->animationList->setCurrentItem(tempAnimationListItem);

        currentSprite->AddAnimation(temporaryAnimation);
    }
    //otherwise, throw out the values and clear the form
    else
    {
        delete temporaryAnimation;
    }

}

void SpriteEditor::on_deleteAnimationButton_clicked()
{
    //check if there is anything selected
    if(IsAnimationSelected())
    {
        QMessageBox warning;

        //double check that they actually meant to delete the animation
        if(warning.question(this, "Confirm", "Are you sure you want to delete this animation?", warning.Ok, warning.No)
                == warning.Ok)
        {
            //remove the item from the list and sprite
            currentSprite->DeleteAnimation(GetSelectedAnimation()->GetID());
            delete ui->animationList->currentItem();
        }
    }
}

void SpriteEditor::on_editAnimationButton_clicked()
{
    //create the editor dialog if it does not already exist
    if(animationEditor == 0)
    {
        animationEditor = new AnimationEditor;
    }

    //check if there is anything selected
    if(IsAnimationSelected())
    {
        //retrieve the list item
        AnimationListItem *tempItem = GetSelectedAnimationItem();

        //notify the animation editor about the items animation
        animationEditor->EditAnimation(tempItem->GetAnimation());

        //if the dialog is accepted
        if(animationEditor->exec() == QDialog::Accepted)
        {
            //reset the name of the item so it appears correctly
            tempItem->setText(tempItem->GetAnimation()->GetName());
        }
    }

}

void SpriteEditor::on_previewButton_clicked()
{
    //create the animation previewer
    if(animationPreviewer == 0)
        animationPreviewer = new AnimationPreviewer;

    if(IsAnimationSelected() && IsSpritesheetLoaded())
    {
        QPixmap temporaryPixmap = imageItem->pixmap();
        animationPreviewer->Load(&temporaryPixmap, GetSelectedAnimation());
        animationPreviewer->exec();
    }
}

void SpriteEditor::on_addFrameButton_clicked()
{
    //check if an animation is selected
    if(IsAnimationSelected())
    {
        //create a new frame object
        Frame *newFrame = new Frame;

        //add the frame object to the selected animation
        GetSelectedAnimation()->AddFrame(newFrame);

        //check if a selection box has been drawn
        if(!imageScene.GetSelectionRect().isNull() && !IsFrameSelected())
            //if so, automatically associate that selection box
            newFrame->SetFrameRect(imageScene.GetSelectionRect());

        //repopulate the frame list
        RepopulateFrameList();

    }

}

void SpriteEditor::on_deleteFrameButton_clicked()
{
    //check if an animation is selected
    if(IsAnimationSelected())
    {
        //and if a frame is selected
        if(IsFrameSelected())
        {
            //confirm that they want to delete the frame
            QMessageBox confirmation;

            if(confirmation.question(this, "Confirm", "Are you sure you want to delete this frame?", confirmation.Ok, confirmation.No))
            {
                //delete the frame
                GetSelectedAnimation()->DeleteFrame(GetSelectedFrame()->GetID());

                RepopulateFrameList();
            }
        }
    }
}

void SpriteEditor::on_animationList_currentRowChanged(int currentRow)
{
    RepopulateFrameList();
}

void SpriteEditor::on_frameList_currentRowChanged(int currentRow)
{
    //if a frame is selected
    if(IsFrameSelected())
    {
        //update the frame selection
        imageScene.UpdateSelectionRect(GetSelectedFrame()->GetFrameRect());
        //update the render spot
        imageScene.UpdateRenderSpot(GetSelectedFrame()->GetRenderSpot());

        //put its frame delay value into the delay input
        ui->frameDelayInput->setValue(GetSelectedFrame()->GetDelay());
    }
    else
    {
        //nullify the selection rect
        imageScene.UpdateSelectionRect(QRect(0, 0, 0, 0));
        //hide the render spot
        imageScene.HideRenderSpot();
    }
}

void SpriteEditor::on_selectSpritesheetButton_clicked()
{
    //create the spritesheet selector if it hasnt already been created
    if(spritesheetSelector == NULL)
    {
        spritesheetSelector = new SpritesheetSelector;
        spritesheetSelector->RegisterResourceManager(resourceManager);
    }

    spritesheetSelector->RepopulateImageList();

    //if the user completes the dialog
    if(spritesheetSelector->exec() == QDialog::Accepted)
    {
        //set the sprites image based on what has been selected
        currentSprite->SetImageID(spritesheetSelector->GetSelectedImage()->GetID());
        UpdateDisplayImage();
        spritesheetLoaded = true;
    }

}

void SpriteEditor::on_frameDelayInput_valueChanged(int arg1)
{
    //if a frame is selected when the value changes in the delay input
    if(IsFrameSelected())
    {
        //put that new value into the frame
        GetSelectedFrame()->SetDelay(ui->frameDelayInput->value());
    }
}

void SpriteEditor::on_zoominTool_clicked()
{
    //check that the zoom level is not too big
    if(zoomLevel <= 4)
    {
        //reset the scale
        ui->imageView->scale(1/zoomLevel, 1/zoomLevel);

        //increase the zoom level
        if(zoomLevel >= 1)
            zoomLevel += 1;
        else
            zoomLevel += 0.2;

        ui->zoomLevelLabel->setText(QString::number(zoomLevel * 100) + "% Zoom");

        //set the new scale
        ui->imageView->scale(zoomLevel, zoomLevel);
    }
}

void SpriteEditor::on_zoomoutTool_clicked()
{
    //check that the zoom level is not too small
    if(zoomLevel > 0.4)
    {
        //reset the scale
        ui->imageView->scale(1/zoomLevel, 1/zoomLevel);

        //decrease the zoom level
        if(zoomLevel > 1)
            zoomLevel -= 1;
        else
            zoomLevel -= 0.2;

        ui->zoomLevelLabel->setText(QString::number(zoomLevel * 100) + "% Zoom");

        //set the new scale
        ui->imageView->scale(zoomLevel, zoomLevel);
    }
}

void SpriteEditor::on_spriteNameInput_textChanged(const QString &arg1)
{
    if(currentSprite == NULL)
        return;

    currentSprite->SetName(arg1);
}


