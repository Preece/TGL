#ifndef DELETESPRITECOMMAND_H
#define DELETESPRITECOMMAND_H

#include <QUndoCommand>

#include "../Model/Sprite.h"

class DeleteSpriteCommand : public QUndoCommand
{
public:
    DeleteSpriteCommand(Sprite *newSprite, QList<Sprite*> *sprites);
    ~DeleteSpriteCommand();

    virtual void undo();
    virtual void redo();

    bool ListContainsSprite();

private:
    Sprite *sprite;
    QList<Sprite*> *spriteListPtr;
};

#endif // DELETESPRITECOMMAND_H
