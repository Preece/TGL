#ifndef PENCILBRUSH_H
#define PENCILBRUSH_H

#include "TileBrush.h"
#include "../LayerGroup.h"

class PencilBrush : public TileBrush
{
public:
    PencilBrush();

    void Paint(int x, int y, LayerGroup *layer, bool preview = false);

    void SetSelectedTileID(int newID) { selectedTileID = newID; }
private:

    int selectedTileID;
};

#endif // PENCILBRUSH_H
