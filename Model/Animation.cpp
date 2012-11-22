#include "Animation.h"

void Animation::DestroyAllFrames()
{
    //loop through and destroy all frames
    for(int i = 0; i < frameList.count(); i++)
    {
        delete frameList[i];
    }

    frameList.clear();
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
    return frameList.count();
}

Frame *Animation::GetFrameAtIndex(int i)
{
    if(i >= frameList.count() || i < 0)
        return NULL;

    return frameList[i];
}

void Animation::AddFrame(Frame *newFrame)
{
    //put the new frame at the rear of the frame list
    frameList.push_back(newFrame);
}

void Animation::DeleteFrame(int ID)
{
    //loop through the frames
    for(int i = 0; i < GetFrameCount(); i++)
    {
        //check their ID's against the paramater
        if(frameList[i]->GetID() == ID)
        {
            //if it matches, delete it
            delete frameList[i];
            frameList.removeAt(i);
        }
    }
}
