#ifndef ADDTILESCOMMAND_H
#define ADDTILESCOMMAND_H

#include <QUndoCommand>

#include "../Model/TileInstance.h"
#include "../Model/Layer.h"

class AddTilesCommand : public QUndoCommand
{
public:
    AddTilesCommand(Layer * newLayer, int newX, int newY, int newT);

    void undo();
    void redo();

    TileInstance *GetTileInstance() { return tile; }

private:
    int x, y, newType;
    Layer *layer;
    TileInstance *tile;
};

#endif // ADDTILESCOMMAND_H
