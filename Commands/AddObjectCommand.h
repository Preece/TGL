#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include <QUndoCommand>

class AddObjectCommand : public QUndoCommand
{
public:
    AddObjectCommand();

    void undo();
    void redo();

private:
};

#endif // ADDOBJECTCOMMAND_H
