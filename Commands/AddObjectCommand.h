#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include <QUndoCommand>

class AddObjectCommand : public QUndoCommand
{
public:
    AddObjectCommand();
};

#endif // ADDOBJECTCOMMAND_H
