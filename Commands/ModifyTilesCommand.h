#ifndef MODIFYTILESCOMMAND_H
#define MODIFYTILESCOMMAND_H

#include <QUndoCommand>

#include "../Model/TileLayer.h"

class ModifyTilesCommand : public QUndoCommand
{
public:
    ModifyTilesCommand(TileLayer * newLayer, int newX, int newY, int newOX, int newOY, int oldOX, int oldOY);

    void undo();
    void redo();

private:
    TileLayer *holdLayer;
    int x, y;
    int newOriginX, newOriginY;
    int oldOriginX, oldOriginY;
};

#endif // MODIFYTILESCOMMAND_H
