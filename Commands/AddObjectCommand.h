#ifndef ADDOBJECTCOMMAND_H
#define ADDOBJECTCOMMAND_H

#include <QUndoCommand>

#include "../Model/ObjectInstance.h"

class AddObjectCommand : public QUndoCommand
{
public:
    AddObjectCommand(Sprite *newSprite, QList<Sprite*> *sprites);
    ~AddObjectCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsObject();

private:
    Sprite *sprite;
    QList<Sprite*> *spriteList;
};

#endif // ADDOBJECTCOMMAND_H
