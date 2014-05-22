#ifndef EXPORTER_H
#define EXPORTER_H

#include <QObject>

#include "../Model/ResourceController.h"

class Exporter : public QObject
{
    Q_OBJECT
public:
    explicit Exporter(QObject *parent = 0);

    virtual Export(ResourceController *resources) = 0;
    virtual Import(ResourceController *resources) = 0;

signals:

public slots:

};

#endif // EXPORTER_H
