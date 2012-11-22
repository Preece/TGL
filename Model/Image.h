#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QFile>
#include <QMessageBox>

#include "Savable.h"

class Image : public Savable
{
private:
    QImage *image;

public:
    Image();
    ~Image();

    bool SaveToFile(QFile &file);
    bool LoadFromFile(QFile &file);

    void SetImage(QImage *newImage) { image = newImage; }
    void SetImageFromFile(QString filename);
    QImage *GetImage() { return image; }
};

#endif // IMAGE_H
