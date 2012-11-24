#include "Image.h"

Image::Image()
{
    image = NULL;
}

Image::~Image()
{
    if(image)
        delete image;
}

bool Image::SaveToFile(QFile &file)
{
    return false;
}

bool Image::LoadFromFile(QFile &file)
{
    return false;
}

void Image::SetImageFromFile(QString filename)
{
    //check if the image already exists
    if(image != NULL)
    {
        //if so, delete it and nullify it
        delete image;
        image = 0;
    }

    //create a new image
    image = new QImage;
    //and load it from the specified filename
    image->load(filename);

    if(image->isNull())
        QMessageBox::warning(NULL, "Warning", "The Image Failed To Load.");
}

QImage *Image::GetImage()
{
    if(image == NULL)
    {
        QMessageBox::warning(NULL, "Warning", "You tried to get an image, but it was NULL!");
        return NULL;
    }

    return image;
}
