#include "ModifyTilesCommand.h"

ModifyTilesCommand::ModifyTilesCommand()
{
    initialRedo = true;
}

void ModifyTilesCommand::AddModification(TileLayer *layer, int newX, int newY, TileCoord newOrgn, TileCoord oldOrgn)
{
	//fill out a new tile modification structure
	TileModification newMod;
	newMod.layer = layer;
	newMod.x = newX;
	newMod.y = newY;
	newMod.newOrigin = newOrgn;
	newMod.oldOrigin = oldOrgn;

    //add the new modification keyed by its position. Its ok if it overwrites
    //another modification because only the most recent one matters
    mods.insert(TileCoord(newMod.x, newMod.y), newMod);
}

int ModifyTilesCommand::GetModificationCount()
{
    return mods.count();
}

TileCoord ModifyTilesCommand::GetTileOrigin(int x, int y)
{
    //if a modification exists at this position, return it
    if(mods.contains(TileCoord(x, y)))
        return mods[TileCoord(x, y)].newOrigin;

    //otherwise return a null tile
    return TileCoord(-1, -1);
}

void ModifyTilesCommand::undo()
{
    QHash<TileCoord, TileModification>::iterator iter;

    for(iter = mods.begin(); iter != mods.end(); ++iter)
    {
        iter.value().layer->ModifyTile(iter.value().x, iter.value().y, iter.value().oldOrigin);
    }
}

void ModifyTilesCommand::redo()
{
    QHash<TileCoord, TileModification>::iterator iter;

    for(iter = mods.begin(); iter != mods.end(); ++iter)
    {
        iter.value().layer->ModifyTile(iter.value().x, iter.value().y, iter.value().newOrigin);

        //if this is not the initial redo, cause a painting event
    }

    initialRedo = false;
}
