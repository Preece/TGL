#ifndef STAMPBRUSH_H
#define STAMPBRUSH_H

#include <QList>

#include "TileBrush.h"

class StampBrush : public TileBrush
{
public:
    StampBrush();

private:
    int width, height;
    QList<int> tiles;
};

#endif // STAMPBRUSH_H
