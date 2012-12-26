#ifndef TILE_H
#define TILE_H

#include "Savable.h"

class Tile : public Savable
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "TILE"; }

    Tile();

    void SetCollision(int newType) { collision = newType; }
    int GetCollision();

    void SetOrigin(int newX, int newY) { originX = newX; originY = newY; }
    void SetXOrigin(int newX) { originX = newX; }
    void SetYOrigin(int newY) { originY = newY; }
    int GetXOrigin() { return originX; }
    int GetYOrigin() { return originY; }

    int GetTilesheetID() { return tilesheetID; }
    void SetTilesheetID(int newID) { tilesheetID = newID; }

private:
    int originX, originY;
    int collision;

    int tilesheetID;
};

#endif // TILE_H
