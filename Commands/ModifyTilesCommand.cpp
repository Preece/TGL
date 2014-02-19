#include "ModifyTilesCommand.h"

ModifyTilesCommand::ModifyTilesCommand(TileLayer *newLayer, int newX, int newY, int newOX, int newOY, int oldOX, int oldOY)
{
    holdLayer = newLayer;
    x = newX;
    y = newY;
    newOriginX = newOX;
    newOriginY = newOY;
    oldOriginX = oldOX;
    oldOriginY = oldOY;

}

void ModifyTilesCommand::undo()
{
    holdLayer->ModifyTile(x, y, oldOriginX, oldOriginY);
}

void ModifyTilesCommand::redo()
{
    holdLayer->ModifyTile(x, y, newOriginX, newOriginY);
}
