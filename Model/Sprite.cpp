#include "Sprite.h"

bool Sprite::LoadFromFile(Exporter *exporter)
{
    return false;
}

Sprite::Sprite()
{
    imageID = 0;
}

bool Sprite::SaveToFile(Exporter *exporter)
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
    AddChild(newAnimation);
}

void Sprite::DeleteAnimation(int ID)
{
    RemoveChild(ID);
}

void Sprite::SetImageID(int newImageID)
{
    imageID = newImageID;
}

Animation *Sprite::GetAnimationByIndex(int index)
{
    return static_cast<Animation*>(GetChildByIndex(index));
}
