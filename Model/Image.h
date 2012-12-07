#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QFile>
#include <QMessageBox>

#include "Savable.h"

class Image : public Savable
{
public:
    bool SaveToFile(Exporter *exporter);
    bool LoadFromFile(Exporter *exporter);
    QString GetType() { return "IMAG"; }

    Image();
    ~Image();

    void SetImage(QImage *newImage) { image = newImage; }
    void SetImageFromFile(QString filename);
    QImage *GetImage();

private:
    QImage *image;
};

#endif // IMAGE_H
