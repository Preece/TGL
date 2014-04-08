#ifndef ADDTILESCOMMAND_H
#define ADDTILESCOMMAND_H

#include <QUndoCommand>

#include "../Model/TileLayer.h"

class AddTilesCommand : public QUndoCommand
{
public:
    AddTilesCommand(TileLayer * newLayer, TileCoord pos, TileCoord origin);

    void undo();
    void redo();

    Tile *GetTile() { return tile; }

private:
    TileCoord newPos;
    TileCoord newOrigin;
    TileLayer *layer;
    Tile *tile;
};

#endif // ADDTILESCOMMAND_H
