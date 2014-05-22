#ifndef JSONEXPORTER_H
#define JSONEXPORTER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "Exporter.h"

class JSONExporter : public Exporter
{
public:
    JSONExporter();

    void Export(ResourceController *resources);
    void Import(ResourceController *resources);
};

#endif // JSONEXPORTER_H
