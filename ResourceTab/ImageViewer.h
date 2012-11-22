#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QDialog>
#include <QImage>

#include "../Model/Image.h"

namespace Ui {
class ImageViewer;
}

class ImageViewer : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImageViewer(QWidget *parent = 0);
    ~ImageViewer();

    void DisplayImage(Image *display);
    
private:
    Ui::ImageViewer *ui;
};

#endif // IMAGEVIEWER_H
