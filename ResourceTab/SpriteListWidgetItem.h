#ifndef SPRITESELECTORITEM_H
#define SPRITESELECTORITEM_H

#include <QListWidgetItem>
#include "../Model/Sprite.h"

class SpriteListWidgetItem : public QListWidgetItem
{
private:
    Sprite *sprite;

public:
    SpriteListWidgetItem();

    void SetSprite(Sprite *newSprite);
    Sprite *GetSprite();
};

#endif // SPRITESELECTORITEM_H
