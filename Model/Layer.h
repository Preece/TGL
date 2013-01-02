#ifndef LAYER_H
#define LAYER_H

#include <QGraphicsItemGroup>

#include "Savable.h"
#include "TileInstance.h"

class Layer : public Savable
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "LAYR"; }

    Layer();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    void SetVerticalParallax(double newVP) { verticalParallax = newVP; }
    double GetVerticalParallax() { return verticalParallax; }
    void SetHorizontalParallax(double newHP) { horizontalParallax = newHP; }
    double GetHorizontalParallax() { return horizontalParallax; }

    void SetOpacity(int newOpacity) { opacity = newOpacity; if(opacity > 100) opacity = 100; }
    int GetOpacity() { return opacity; }

    int GetTileCount() { return GetChildCount(); }
    TileInstance *GetTileAtIndex(int index);

    TileInstance *AddTile(int x = 0, int y = 0, int ID = 0);
    void RemoveTile(int x, int y);
    void ModifyTile(int x, int y, int ID);

private:
    double verticalParallax, horizontalParallax;
    QString name;

    int opacity;
};

#endif // LAYER_H
