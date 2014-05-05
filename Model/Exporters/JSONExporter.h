#include <QString>

#include "Exporter.h"
#include "../ResourceManager.h"

class JSONExporter : public Exporter
{
    JSONExporter();
    ~JSONExporter();
    
    bool Export(ResourceManager *resources, QString filename);
    bool Import(ResourceManager *resources, QString filename);
};
