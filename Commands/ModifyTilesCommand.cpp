#include "ModifyTilesCommand.h"

ModifyTilesCommand::ModifyTilesCommand(Layer *newLayer, int newX, int newY, int newT, int oldT)
{
    holdLayer = newLayer;
    x = newX;
    y = newY;
    newType = newT;
    oldType = oldT;
}

void ModifyTilesCommand::undo()
{
    holdLayer->ModifyTile(x, y, oldType);
}

void ModifyTilesCommand::redo()
{
    holdLayer->ModifyTile(x, y, newType);
}
