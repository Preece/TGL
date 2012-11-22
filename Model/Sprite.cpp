#include "Sprite.h"

bool Sprite::LoadFromFile(QFile &file)
{
    return false;
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

void Sprite::SetImageID(int newImageID)
{
    imageID = newImageID;
}
