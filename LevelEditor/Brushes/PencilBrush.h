#ifndef PENCILBRUSH_H
#define PENCILBRUSH_H

#include "TileBrush.h"
#include "../LayerGroup.h"

class PencilBrush : public TileBrush
{
public:
    PencilBrush();

    void Paint(int x, int y, LayerGroup *layer);
    void Line(int x1, int y1, int x2, int y2, LayerGroup *layer);

    void SetSelectedTileID(int newID) { selectedTileID = newID; }
private:

    int size;
    bool overwrite;

    int selectedTileID;
};

#endif // PENCILBRUSH_H
