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

    void ModifyTile(int x, int y, int ID);
    int GetTileType(int x, int y);

    int GetTileCount() { return GetChildCount(); }
    TileInstance *GetTileAtIndex(int index);
    TileInstance *GetTileAtPosition(int x, int y);

    void SetLayerSize(int w, int h);

private:
    int verticalParallax, horizontalParallax;
    QString name;

    QList<QList<TileInstance*> > tiles; //2 dimensional array of pointers
    int width, height;
};

#endif // LAYER_H
