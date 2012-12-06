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
    for(int i = 0; i < children.count(); i++)
    {
        static_cast<Animation*>(children[i])->DestroyAllFrames();
        delete children[i];
    }

    children.clear();
}

void Sprite::AddAnimation(Animation *newAnimation)
{
    children.push_back(newAnimation);
}

void Sprite::DeleteAnimation(int ID)
{
    //loop through and destroy all animations
    for(int i = 0; i < children.count(); i++)
    {
        if(children[i]->GetID() == ID)
        {
            static_cast<Animation*>(children[i])->DestroyAllFrames();
            delete children[i];
            children.removeAt(i);
        }
    }
}

void Sprite::SetImageID(int newImageID)
{
    imageID = newImageID;
}

Animation *Sprite::GetAnimationByIndex(int index)
{
    if(index >= 0 && index < children.count())
        return static_cast<Animation*>(children[index]);

    return NULL;
}
