#include "ModifyTilesCommand.h"

ModifyTilesCommand::ModifyTilesCommand()
{
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

	//add the new modification to the end of the list
	mods.push_back(newMod);
}

void ModifyTilesCommand::undo()
{
	//loop backwards through the list of modifications
	for(int i = (mods.count() - 1); i >= 0; i--)
	{
	    //if the old origin was empty
	    if(mods[i].oldOrigin == TileCoord(-1, -1))
	    {
	        //then remove the tile entirely
	        holdLayer->RemoveTile(TileCoord(mods[i].x, mods[i].y));
	    }
	    //if the old origin was not empty
	    else
	    {
	        //then restore the original origin of the tile
            holdLayer->ModifyTile(mods[i].x, mods[i].y, mods[i].oldOrigin);
        }
    }
}

void ModifyTilesCommand::redo()
{
	//loop through the list of modifications
	for(int i = 0; i < mods.count(); i++)
	{
	    //check if the old origin was empty
	    if(mods[i].oldOrigin == TileCoord(-1, -1))
	    {
	        //if so, add a new tile
	        mods[i].layer->AddTile(mods[i].x, mods[i].y, mods[i].newOrigin);
	    }
	    //if the old origin was not empty
	    else
	    {
	        //modify the existing tile
            mods[i].layer->ModifyTile(mods[i].x, mods[i].y, (mods[i].newOrigin);
        }
    }
}
