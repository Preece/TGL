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
    void SetSize(int newSize) { size = newSize; }
    void SetOverwrite(bool over) { overwrite = over; }
private:

    int size;
    bool overwrite;

    int selectedTileID;
};

#endif // PENCILBRUSH_H
