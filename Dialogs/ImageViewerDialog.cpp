#include "ImageViewerDialog.h"
#include "ui_ImageViewerDialog.h"

ImageViewerDialog::ImageViewerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageViewerDialog)
{
    ui->setupUi(this);
}

ImageViewerDialog::~ImageViewerDialog()
{
    delete ui;
}

void ImageViewerDialog::DisplayImage(Image *display)
{
    //set the size of the label to match the size of the image
    ui->imageLabel->resize(display->GetImage()->width(), display->GetImage()->height());
    this->resize(display->GetImage()->width() + 100, display->GetImage()->height() + 100);

    //display the image
    ui->imageLabel->setPixmap(QPixmap::fromImage(*display->GetImage()));
}
