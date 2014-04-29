#ifndef PENCILBRUSH_H
#define PENCILBRUSH_H

#include "TileBrush.h"
#include "../TileLayerView.h"

class PencilBrush : public TileBrush
{
public:
    PencilBrush();
    ~PencilBrush();

    void Paint(int x, int y, ResourceManager *resources, bool preview = false);

    QString GetType() { return "pencil"; }

    void SetLineMode(bool state) { lineMode = state; }
    bool GetLineMode() { return lineMode; }
private:



    bool lineMode;
};

#endif // PENCILBRUSH_H
