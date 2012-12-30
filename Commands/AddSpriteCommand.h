#ifndef ADDSPRITECOMMAND_H
#define ADDSPRITECOMMAND_H

#include <QUndoCommand>
#include "../Model/Sprite.h"

class AddSpriteCommand : public QUndoCommand
{
public:
    AddSpriteCommand(Sprite *newSprite, QList<Sprite*> *sprites);
    ~AddSpriteCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsSprite();

private:
    Sprite *sprite;
    QList<Sprite*> *spriteList;
};

#endif // ADDSPRITECOMMAND_H
