#include "Image.h"

Image::Image()
{
    image = NULL;

    AddProperty("Image Name", "New Image");
    AddProperty("File Name", QVariant());
}

Image::~Image()
{
    if(image)
        delete image;
}

void Image::SetImageFromFile(QString file)
{
    //check if the image already exists
    if(image != NULL)
    {
        //if so, delete it and nullify it
        delete image;
        image = NULL;
    }

    //create a new image
    image = new QImage;
    //and load it from the specified filename
    image->load(file);

    SetProperty("Image Name", QFileInfo(file).fileName());
    SetProperty("File Name", file);
}

QImage *Image::GetImage()
{
    return image;
}
