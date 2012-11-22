#include "ImageSelectorItem.h"

ImageSelectorItem::ImageSelectorItem()
{
    image = NULL;
}

void ImageSelectorItem::SetImage(Image *newImage)
{
    //assign the image
    image = newImage;

    //assign the icon as a small version of the image
    QIcon newIcon;
    newIcon.addPixmap(QPixmap::fromImage(*(image->GetImage())));

    setIcon(newIcon);

}

Image *ImageSelectorItem::GetImage()
{
    if(image == NULL)
            QMessageBox::warning(NULL, "Warning", "You tried to get an Image from an ImageSelectorItem. But it has no associated image.");

    return image;
}
