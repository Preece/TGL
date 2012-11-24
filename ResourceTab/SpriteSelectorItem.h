#ifndef SPRITESELECTORITEM_H
#define SPRITESELECTORITEM_H

#include <QListWidgetItem>
#include "../Model/Sprite.h"

class SpriteSelectorItem : public QListWidgetItem
{
private:
    Sprite *sprite;

public:
    SpriteSelectorItem();

    void SetSprite(Sprite *newSprite);
    Sprite *GetSprite();
};

#endif // SPRITESELECTORITEM_H
