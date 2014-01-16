#ifndef MODIFYTILESCOMMAND_H
#define MODIFYTILESCOMMAND_H

#include <QUndoCommand>

#include "../Model/Layer.h"

class ModifyTilesCommand : public QUndoCommand
{
public:
    ModifyTilesCommand(Layer * newLayer, int newX, int newY, int newT, int oldT);

    void undo();
    void redo();

private:
    Layer *holdLayer;
    int x, y;
    int newType;
    int oldType;
};

#endif // MODIFYTILESCOMMAND_H
