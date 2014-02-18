#ifndef MODIFYTILESCOMMAND_H
#define MODIFYTILESCOMMAND_H

#include <QUndoCommand>

#include "../Model/TileLayer.h"

class ModifyTilesCommand : public QUndoCommand
{
public:
    ModifyTilesCommand(TileLayer * newLayer, int newX, int newY, int newT, int oldT);

    void undo();
    void redo();

private:
    TileLayer *holdLayer;
    int x, y;
    int newType;
    int oldType;
};

#endif // MODIFYTILESCOMMAND_H
