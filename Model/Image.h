#ifndef IMAGE_H
#define IMAGE_H

#include <QImage>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QFileInfo>

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
    void SetImageFromFile(QString file);
    QImage *GetImage();

    void SetFilename(QString newName) { filename = newName; }
    QString GetFilename() { return filename; }

private:
    QImage *image;
    QString filename;
};

#endif // IMAGE_H
