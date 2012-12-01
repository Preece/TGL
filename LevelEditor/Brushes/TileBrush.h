#ifndef TILEBRUSH_H
#define TILEBRUSH_H

class TileBrush
{
private:

public:
    TileBrush();

    //in the mouse event handler, this is called. The brush subclasses
    //reimplement helper functions inside of it to define the custom
    //functionality of that brush.
    void MouseEvent(QPoint pos, LevelLayer * layer, bool mouseDown);
};

#endif // TILEBRUSH_H
