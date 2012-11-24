#include "SpriteSelectorItem.h"

SpriteSelectorItem::SpriteSelectorItem()
{
    sprite = 0;
}

void SpriteSelectorItem::SetSprite(Sprite *newSprite)
{
    sprite = newSprite;

    if(sprite == NULL)
        return;

    setText(sprite->GetName());
}

Sprite *SpriteSelectorItem::GetSprite()
{
    return sprite;
}
