#ifndef DELETEOBJECTINSTANCECOMMAND_H
#define DELETEOBJECTINSTANCECOMMAND_H

#include <QUndoCommand>

class DeleteObjectInstanceCommand : public QUndoCommand
{
public:
    DeleteObjectInstanceCommand();
};

#endif // DELETEOBJECTINSTANCECOMMAND_H
