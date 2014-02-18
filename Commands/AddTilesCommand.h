#ifndef ADDTILESCOMMAND_H
#define ADDTILESCOMMAND_H

#include <QUndoCommand>

#include "../Model/TileLayer.h"

class AddTilesCommand : public QUndoCommand
{
public:
    AddTilesCommand(TileLayer * newLayer, int newX, int newY, int newT);

    void undo();
    void redo();

    Tile *GetTileInstance() { return tile; }

private:
    int x, y, newType;
    TileLayer *layer;
    Tile *tile;
};

#endif // ADDTILESCOMMAND_H
