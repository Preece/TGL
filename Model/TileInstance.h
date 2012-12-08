#ifndef TILEINSTANCE_H
#define TILEINSTANCE_H

#include "Savable.h"

class TileInstance : public Savable
{
public:
    bool SaveToFile(Exporter *exporter);
    bool LoadFromFile(Exporter *exporter);
    QString GetType() { return "TLIN"; }

    TileInstance() { x = 0; y = 0; tileID = 0; }

    int GetX() { return x; }
    int GetY() { return y; }
    void SetX(int newX) { x = newX; }
    void SetY(int newY) { y = newY; }

    int GetTileID() { return tileID; }
    void SetTileID(int newTileID) { tileID = newTileID; }

private:
    int x;
    int y;
    int tileID;
};

#endif // TILEINSTANCE_H
