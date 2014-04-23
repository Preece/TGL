#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QDialog>
#include <QImage>

#include "../Model/Image.h"

namespace Ui {
class ImageViewerDialog;
}

class ImageViewerDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImageViewerDialog(QWidget *parent = 0);
    ~ImageViewerDialog();

    void DisplayImage(Image *display);
    
private:
    Ui::ImageViewerDialog *ui;
};

#endif // IMAGEVIEWER_H
