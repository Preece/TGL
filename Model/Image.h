#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QFileInfo>

#include "ResourceNode.h"

class Image : public ResourceNode
{
public:
    Image();
    ~Image();

    void SetImage(QImage *newImage) { image = newImage; }
    void SetImageFromFile(QString file);
    QImage *GetImage();

    void SetImageName(QString newName) { SetProperty("Name", newName); }
    QString GetImageName() { return GetProperty("Name").toString(); }

    QString GetFilename() { return GetProperty("File Name").toString(); }

private:
    QImage *image;
};

#endif // IMAGE_H
