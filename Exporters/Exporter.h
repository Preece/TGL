#ifndef EXPORTER_H
#define EXPORTER_H

#include <QObject>

#include "../Model/ResourceController.h"
#include "../Model/TileController.h"

class Exporter : public QObject
{
    Q_OBJECT
public:
    explicit Exporter(QObject *parent = 0);

    virtual void Export(ResourceController *resources, QString filename) = 0;
    virtual void Import(ResourceController *resources, TileController *tiles, QString filename) = 0;

signals:

public slots:

protected:


};

#endif // EXPORTER_H
