#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItemGroup>

#include "Savable.h"
#include "TileInstance.h"

class Layer : public Savable, public QGraphicsItemGroup
{
public:
    bool SaveToFile(Exporter *exporter);
    bool LoadFromFile(Exporter *exporter);
    QString GetType() { return "LAYR"; }

    Layer();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    void ModifyTile(int x, int y, int ID);
    int GetTileType(int x, int y);

    int GetTileCount() { return GetChildCount(); }
    TileInstance *GetTileAtIndex(int index);

private:
    int verticalParallax, horizontalParallax;
    QString name;
};

#endif // LAYER_H
