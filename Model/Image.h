#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QFile>
#include <QMessageBox>

#include "ItemNode.h"

class Image : public ItemNode
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "image"; }

    Image();
    ~Image();

    void SetImage(QImage *newImage) { image = newImage; }
    void SetImageFromFile(QString filename);
    QImage *GetImage();

private:
    QImage *image;
};

#endif // IMAGE_H
