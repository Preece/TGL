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
    return children.count();
}

Frame *Animation::GetFrameAtIndex(int i)
{
    if(i >= children.count() || i < 0)
        return NULL;

    return static_cast<Frame*>(children[i]);
}

void Animation::AddFrame(Frame *newFrame)
{
    //put the new frame at the rear of the frame list
    children.push_back(newFrame);
}

void Animation::DeleteFrame(int ID)
{
    //loop through the frames
    for(int i = 0; i < GetFrameCount(); i++)
    {
        //check their ID's against the paramater
        if(children[i]->GetID() == ID)
        {
            //if it matches, delete it
            delete children[i];
            children.removeAt(i);
        }
    }
}
