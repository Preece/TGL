#ifndef PENCILBRUSH_H
#define PENCILBRUSH_H

#include "TileBrush.h"
#include "../LayerGroup.h"

class PencilBrush : public TileBrush
{
public:
    PencilBrush();

    void Paint(int x, int y, LayerGroup *layer, bool preview = false);

    QString GetType() { return "pencil"; }

    void SetSelectedTileID(int newID) { selectedTileID = newID; }

    void SetLineMode(bool state) { lineMode = state; }
    bool GetLineMode() { return lineMode; }
private:

    int selectedTileID;

    bool lineMode;
};

#endif // PENCILBRUSH_H
