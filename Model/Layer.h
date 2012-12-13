#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItemGroup>

#include "Savable.h"
#include "TileInstance.h"

class Layer : public Savable
{
public:
    bool SaveToFile(Exporter *exporter);
    bool LoadFromFile(Exporter *exporter);
    QString GetType() { return "LAYR"; }

    Layer();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    int GetTileCount() { return GetChildCount(); }
    TileInstance *GetTileAtIndex(int index);

    TileInstance *AddTile(int x = 0, int y = 0, int ID = 0);

private:
    int verticalParallax, horizontalParallax;
    QString name;
};

#endif // LAYER_H
