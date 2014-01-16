#ifndef MOVEOBJECTCOMMAND_H
#define MOVEOBJECTCOMMAND_H

#include <QUndoCommand>

class MoveObjectCommand : public QUndoCommand
{
public:
    MoveObjectCommand();

    void undo();
    void redo();

private:
};

#endif // MOVEOBJECTCOMMAND_H
