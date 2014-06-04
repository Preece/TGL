#ifndef JSONEXPORTER_H
#define JSONEXPORTER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include "Exporter.h"

class JSONExporter : public Exporter
{
public:
    JSONExporter();

    void Export(ResourceController *resources, QString filename);
    void Import(ResourceController *resources, TileController *tiles, QString filename);

private:
    QJsonObject ResourcePropertiesToJSON(ResourceNode* resource);
};

#endif // JSONEXPORTER_H
