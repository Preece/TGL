#ifndef IMAGESELECTORITEM_H
#define IMAGESELECTORITEM_H

#include <QListWidgetItem>

#include "../Model/Image.h"

class ImageSelectorItem : public QListWidgetItem
{
private:
    Image *image;

public:
    ImageSelectorItem();

    void SetImage(Image *newImage);
    Image *GetImage();
};

#endif // IMAGESELECTORITEM_H
