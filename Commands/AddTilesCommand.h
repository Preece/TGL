#ifndef ADDTILESCOMMAND_H
#define ADDTILESCOMMAND_H

#include <QUndoCommand>

#include "../Model/TileLayer.h"

class AddTilesCommand : public QUndoCommand
{
public:
    AddTilesCommand(TileLayer * newLayer, int newX, int newY, int newOX, int newOY);

    void undo();
    void redo();

    Tile *GetTile() { return tile; }

private:
    int x, y, newOriginX, newOriginY;
    TileLayer *layer;
    Tile *tile;
};

#endif // ADDTILESCOMMAND_H
