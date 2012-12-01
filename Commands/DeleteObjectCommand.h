#ifndef DELETEOBJECTCOMMAND_H
#define DELETEOBJECTCOMMAND_H

#include <QUndoCommand>

class DeleteObjectCommand : public QUndoCommand
{
public:
    DeleteObjectCommand();
};

#endif // DELETEOBJECTCOMMAND_H
