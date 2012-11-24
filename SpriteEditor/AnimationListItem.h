#ifndef ANIMATIONLISTITEM_H
#define ANIMATIONLISTITEM_H

#include <QListWidgetItem>

#include "Model/Animation.h"

class AnimationListItem : public QListWidgetItem
{
private:
    Animation *animationItem;

public:
    AnimationListItem();
    ~AnimationListItem();

    void CreateNewAnimation();
    void SetAnimation(Animation *existingAnimation);

    Animation *GetAnimation();
};

#endif // ANIMATIONLISTITEM_H
