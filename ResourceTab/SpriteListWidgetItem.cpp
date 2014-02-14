#include "SpriteListWidgetItem.h"

SpriteListWidgetItem::SpriteListWidgetItem()
{
    sprite = 0;
}

void SpriteListWidgetItem::SetSprite(Sprite *newSprite)
{
    sprite = newSprite;

    if(sprite == NULL)
        return;

    setText(sprite->GetName());
}

Sprite *SpriteListWidgetItem::GetSprite()
{
    return sprite;
}
