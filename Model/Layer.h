#ifndef LAYER_H
#define LAYER_H

#include "Savable.h"

class Layer : public Savable
{
public:
    bool SaveToFile(QFile &file);
    bool LoadFromFile(QFile &file);
    QString GetType() { return "LAYR"; }

    Layer();

private:

};

#endif // LAYER_H
