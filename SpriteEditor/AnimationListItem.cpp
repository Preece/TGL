#include "AnimationListItem.h"

AnimationListItem::AnimationListItem()
{
    animationItem = 0;
}

AnimationListItem::~AnimationListItem()
{
}

void AnimationListItem::SetAnimation(Animation *existingAnimation)
{
    //set the animation pointer to the existing animation
    animationItem = existingAnimation;

    //set the name of the list item to the name of the animation
    setText(animationItem->GetName());
}

Animation *AnimationListItem::GetAnimation()
{
    return animationItem;
}
