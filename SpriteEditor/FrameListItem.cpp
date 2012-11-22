#include "FrameListItem.h"

FrameListItem::FrameListItem()
{
    frameItem = 0;
}

FrameListItem::~FrameListItem()
{
}

void FrameListItem::CreateNewFrame()
{
    if(frameItem != 0)
            DestroyFrame();

    frameItem = new Frame;
}

void FrameListItem::SetFrame(Frame *existingFrame)
{
    //set the frame pointer to the existing frame
    frameItem = existingFrame;

    //set the frames icon to a missing file icon
    SetIcon(NULL);
}

void FrameListItem::SetIcon(QImage *spritesheetImage)
{
    QIcon warningIcon(":/Icons/Icons/MissingFile.png");


    //if the passed image is invalid or no associated frame
    if(spritesheetImage == NULL || frameItem == NULL)
    {
        setIcon(warningIcon);
        return;
    }

    //or there is no frame rect
    if(frameItem->GetFrameRect().isNull())
    {
        setIcon(warningIcon);
        return;
    }

    //otherwise, create a pixmap from the image and frame rect
    //create an icon with that pixmap
    QIcon frameIcon(QPixmap::fromImage(*spritesheetImage));
    //set the icon
    setIcon(frameIcon);
}

Frame *FrameListItem::GetFrame()
{
    return frameItem;
}

void FrameListItem::DestroyFrame()
{
    //frames should not be destroyed from here because they are maintained by the animation!
}
