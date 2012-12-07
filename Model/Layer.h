#ifndef LAYER_H
#define LAYER_H

#include "Savable.h"

class Layer : public Savable
{
public:
    bool SaveToFile(Exporter *exporter);
    bool LoadFromFile(Exporter *exporter);
    QString GetType() { return "LAYR"; }

    Layer();
private:

};

#endif // LAYER_H
