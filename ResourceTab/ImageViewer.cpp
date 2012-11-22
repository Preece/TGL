#include "ImageViewer.h"
#include "ui_ImageViewer.h"

ImageViewer::ImageViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageViewer)
{
    ui->setupUi(this);
}

ImageViewer::~ImageViewer()
{
    delete ui;
}

void ImageViewer::DisplayImage(Image *display)
{
    //set the size of the label to match the size of the image
    ui->imageLabel->resize(display->GetImage()->width(), display->GetImage()->height());
    this->resize(display->GetImage()->width() + 100, display->GetImage()->height() + 100);

    //display the image
    ui->imageLabel->setPixmap(QPixmap::fromImage(*display->GetImage()));
}
