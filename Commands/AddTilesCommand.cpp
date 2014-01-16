#include "AddTilesCommand.h"

AddTilesCommand::AddTilesCommand(Layer *newLayer, int newX, int newY, int newT)
{
    layer = newLayer;
    x = newX;
    y = newY;
    newType = newT;

    tile = NULL;
}

void AddTilesCommand::undo()
{
    layer->RemoveTile(x, y);
    tile = NULL;
}

void AddTilesCommand::redo()
{
    tile = layer->AddTile(x, y, newType);
}
