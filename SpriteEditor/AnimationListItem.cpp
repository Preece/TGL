#include "AnimationListItem.h"

AnimationListItem::AnimationListItem()
{
    animationItem = 0;
}

AnimationListItem::~AnimationListItem()
{
    DestroyAnimation();
}

void AnimationListItem::CreateNewAnimation()
{
    if(animationItem != 0)
            DestroyAnimation();

    animationItem = new Animation;
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

void AnimationListItem::DestroyAnimation()
{
    animationItem->DestroyAllFrames();

    delete animationItem;
    animationItem = 0;
}
