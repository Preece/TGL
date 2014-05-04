#ifndef PENCILBRUSH_H
#define PENCILBRUSH_H

#include "TileBrush.h"

class PencilBrush : public TileBrush
{
public:
    PencilBrush();
    ~PencilBrush();

    void Paint(int x, int y, ResourceManager *resources, bool preview = false);

    QString GetType() { return "pencil"; }
};

#endif // PENCILBRUSH_H
