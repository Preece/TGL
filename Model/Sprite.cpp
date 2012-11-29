#include "Sprite.h"

bool Sprite::LoadFromFile(QFile &file)
{
    return false;
}

Sprite::Sprite()
{
    imageID = 0;
}

bool Sprite::SaveToFile(QFile &file)
{
    return false;
}

void Sprite::DestroyAllAnimations()
{
    //loop through and destroy all animations
    for(int i = 0; i < animations.count(); i++)
    {
        animations[i]->DestroyAllFrames();
        delete animations[i];
    }

    animations.clear();
}

void Sprite::AddAnimation(Animation *newAnimation)
{
    animations.push_back(newAnimation);
}

void Sprite::DeleteAnimation(int ID)
{
    //loop through and destroy all animations
    for(int i = 0; i < animations.count(); i++)
    {
        if(animations[i]->GetID() == ID)
        {
            animations[i]->DestroyAllFrames();
            delete animations[i];
            animations.removeAt(i);
        }
    }
}

void Sprite::SetImageID(int newImageID)
{
    imageID = newImageID;
}

Animation *Sprite::GetAnimationByIndex(int index)
{
    if(index >= 0 && index < animations.count())
        return animations[index];

    return NULL;
}
