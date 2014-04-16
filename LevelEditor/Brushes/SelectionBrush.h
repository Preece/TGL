#ifndef SELECTIONBRUSH_H
#define SELECTIONBRUSH_H

#include <QList>

#include "TileBrush.h"

class SelectionBrush : public TileBrush
{
public:
    SelectionBrush();

    void Move(int x, int y, TileLayerView *layer, bool leftButtonDown);

    void Paint(int x, int y, TileLayerView *layer, bool preview);
    QString GetType() { return "selection"; }


private:
   
};

#endif // SELECTIONBRUSH_H
