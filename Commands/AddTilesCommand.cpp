#include "AddTilesCommand.h"

AddTilesCommand::AddTilesCommand(TileLayer *newLayer, int newX, int newY, int newOX, int newOY)
{
    layer = newLayer;
    x = newX;
    y = newY;
    newOriginX = newOX;
    newOriginY = newOY;

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
