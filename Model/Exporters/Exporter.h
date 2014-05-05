#ifndef EXPORTER_H
#define EXPORTER_H

#include <QString>
#include <QPoint>
#include <QImage>
#include <QRect>

class Exporter
{
public:
    Exporter();
    virtual ~Exporter();

    virtual bool Export(ResourceManager *resources, QString filename) = 0;
    virtual bool Import(ResourceManager *resources, QString filename) = 0;
};

#endif // EXPORTER_H
