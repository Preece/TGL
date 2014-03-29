#ifndef ANIMATION_H
#define ANIMATION_H

#include <QList>

#include "Frame.h"
#include "ItemNode.h"

class Animation : public ItemNode
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "ANMT"; }

    Animation();

    Frame *GetFrame(int ID);
    Frame *GetFrameAtIndex(int i);
    void AddFrame(Frame *newFrame);
    void DeleteFrame(int ID);
    int GetFrameCount();

    int GetNumFrames();

    QString GetName();
    void SetName(QString newName);

    bool GetLoop() { return loop; }
    void SetLoop(bool newLoop) { loop = newLoop; }

    void DestroyAllFrames();

private:
    QString animationName;
    bool loop;
    int nextAnimationID;
};

#endif // ANIMATION_H
