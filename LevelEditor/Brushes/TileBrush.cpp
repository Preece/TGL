#include "TileBrush.h"

TileBrush::TileBrush()
{
}

/*void TileBrush::Line(int x1, int y1, int x2, int y2, LayerGroup *layer)
{
    if(x1 == x2 && y1 == y2)
        return;

    //this function draws a line between the two points
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;

    if(deltaX == 0)
        deltaX = 1;

    double error = 0;
    double deltaError = qAbs(deltaY / deltaX);

    int y = y1;

    //loop through the line on the x axis
    for(int x = x1; x <= x2; x++)
    {
        //paint at each position
        Paint(x, y, layer);

        //and increase the error margin by the slope
        error += deltaError;

        //if the error margin is too high
        if(error >= 0.5)
        {
            //increase the y value
            y++;
            //and reduce the error
            error -= 1.0;
        }
    }
}*/
