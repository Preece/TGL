#include "AddTilesCommand.h"

AddTilesCommand::AddTilesCommand(TileLayer *newLayer, TileCoord pos, TileCoord origin)
{
    layer = newLayer;
    newPos = pos;
    newOrigin = origin;

    tile = NULL;
}

void AddTilesCommand::undo()
{
    layer->RemoveTile(newPos);
    tile = NULL;
}

void AddTilesCommand::redo()
{
    tile = layer->AddTile(newPos, newOrigin);
}
