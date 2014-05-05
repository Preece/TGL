#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QFileInfo>

#include "ItemNode.h"

class Image : public ItemNode
{
public:
    QString GetType() { return "image"; }

    Image();
    ~Image();

    void SetImage(QImage *newImage) { image = newImage; }
    void SetImageFromFile(QString file);
    QImage *GetImage();

    void SetImageName(QString newName) { imageName = newName; }
    QString GetImageName() { return imageName; }

    QString GetFilename() { return filename; }

private:
    QImage *image;
    QString imageName;
    QString filename;
};

#endif // IMAGE_H
