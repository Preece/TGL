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

bool Image::Export(Exporter *exporter)
{
    exporter->WriteImage(*image);

    return true;
}

bool Image::Import(Exporter *exporter)
{
    exporter->ReadImage(*image);

    return true;
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

    imageName = QFileInfo(file).fileName();
    filename = file;
}

QImage *Image::GetImage()
{
    return image;
}
