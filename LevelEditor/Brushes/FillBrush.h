#ifndef FILLBRUSH_H
#define FILLBRUSH_H

#include "TileBrush.h"

class FillBrush : public TileBrush
{
public:
    FillBrush();

    void Paint(int x, int y, LayerGroup *layer, bool preview = false);
    void Fill(int tileX, int tileY, int newTile, int oldTile, LayerGroup *newLayer);

    void SetSelectedTileID(int newID) { selectedTileID = newID; }

private:
    int selectedTileID;
};

#endif // FILLBRUSH_H
