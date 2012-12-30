#include "AddSpriteCommand.h"

AddSpriteCommand::AddSpriteCommand(Sprite *newSprite, QList<Sprite *> *sprites)
{
    sprite = newSprite;
    spriteList = sprites;
}

AddSpriteCommand::~AddSpriteCommand()
{
    //if the sprite is not in the list when this command is destroyed, destroy the sprite
    if(!ListContainsSprite())
    {
        if(sprite)
            delete sprite;
    }
}

void AddSpriteCommand::undo()
{
    for(int i = 0; i < spriteList->count(); i++)
    {
        //if this sprite is the one being held
        if(spriteList->value(i) == sprite)
            spriteList->removeAt(i);
    }
}

void AddSpriteCommand::redo()
{
    spriteList->append(sprite);
}

bool AddSpriteCommand::ListContainsSprite()
{
    for(int i = 0; i < spriteList->count(); i++)
    {
        if(spriteList->value(i) == sprite)
            return true;
    }

    return false;
}
