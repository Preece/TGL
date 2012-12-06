#include "Animation.h"

void Animation::DestroyAllFrames()
{
    //loop through and destroy all frames
    for(int i = 0; i < children.count(); i++)
    {
        delete children[i];
    }

    children.clear();
}

bool Animation::SaveToFile(QFile &file)
{
    return false;
}

bool Animation::LoadFromFile(QFile &file)
{
    return false;
}

Animation::Animation()
{
    loop = false;
    nextAnimationID = 0;
}

QString Animation::GetName()
{
    return animationName;
}

void Animation::SetName(QString newName)
{
    animationName = newName;
}

int Animation::GetFrameCount()
{
    return GetChildCount();
}

Frame *Animation::GetFrameAtIndex(int i)
{
    return static_cast<Frame*>(GetChildByIndex(i));
}

void Animation::AddFrame(Frame *newFrame)
{
    AddChild(newFrame);
}

void Animation::DeleteFrame(int ID)
{
    RemoveChild(ID);
}
