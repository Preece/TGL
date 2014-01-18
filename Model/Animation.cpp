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

bool Animation::Export(Exporter *exporter)
{
    exporter->WriteString(animationName);
    exporter->WriteBool(loop);
    exporter->WriteInt(nextAnimationID);

    return true;
}

bool Animation::Import(Exporter *exporter)
{
    exporter->ReadString(animationName);
    exporter->ReadBool(loop);
    exporter->ReadInt(nextAnimationID);

    return true;
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
    //bounds check
    if(i < 0 || i >= children.count())
        return NULL;

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
