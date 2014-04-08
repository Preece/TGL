#include "ModifyTilesCommand.h"

ModifyTilesCommand::ModifyTilesCommand(TileLayer *newLayer, int newX, int newY, TileCoord newOrgn, TileCoord oldOrgn)
{
    holdLayer = newLayer;
    x = newX;
    y = newY;
    newOrigin = newOrgn;
    oldOrigin = oldOrgn;
}

void ModifyTilesCommand::undo()
{
    holdLayer->ModifyTile(x, y, oldOrigin);
}

void ModifyTilesCommand::redo()
{
    holdLayer->ModifyTile(x, y, newOrigin);
}
