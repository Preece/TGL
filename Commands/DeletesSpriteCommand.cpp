#include "DeleteSpriteCommand.h"

DeleteSpriteCommand::DeleteSpriteCommand(Sprite *newSprite, QList<Sprite *> *sprites)
{
    sprite = newSprite;
    spriteListPtr = sprites;
}

DeleteSpriteCommand::~DeleteSpriteCommand()
{
    //if the sprite is not in the list when this command is destroyed, destroy the sprite
    if(!ListContainsSprite())
    {
        if(sprite)
            delete sprite;
    }
}

void DeleteSpriteCommand::undo()
{
    spriteListPtr->append(sprite);
}

void DeleteSpriteCommand::redo()
{
    for(int i = 0; i < spriteListPtr->count(); i++)
    {
        //if this sprite is the one being held
        if(spriteListPtr->value(i) == sprite)
            spriteListPtr->removeAt(i);
    }
}

bool DeleteSpriteCommand::ListContainsSprite()
{
    for(int i = 0; i < spriteListPtr->count(); i++)
    {
        if(spriteListPtr->value(i) == sprite)
            return true;
    }

    return false;
}
