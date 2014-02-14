#ifndef IMAGESELECTORITEM_H
#define IMAGESELECTORITEM_H

#include <QListWidgetItem>

#include "../Model/Image.h"

class ImageListWidgetItem : public QListWidgetItem
{
private:
    Image *image;

public:
    ImageListWidgetItem();

    void SetImage(Image *newImage);
    Image *GetImage();
};

#endif // IMAGESELECTORITEM_H
