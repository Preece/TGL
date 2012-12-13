#ifndef TILEBRUSH_H
#define TILEBRUSH_H

#include <QPoint>

class TileBrush
{
private:

public:
    TileBrush();

    //in the mouse event handler, this is called. The brush subclasses
    //reimplement helper functions inside of it to define the custom
    //functionality of that brush.
};

#endif // TILEBRUSH_H
