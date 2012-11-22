#ifndef FRAMELISTITEM_H
#define FRAMELISTITEM_H

#include <QListWidgetItem>

#include "Model/Frame.h"

class FrameListItem: public QListWidgetItem
{
private:
    Frame *frameItem;

public:
    FrameListItem();
    ~FrameListItem();

    void CreateNewFrame();
    void SetFrame(Frame *existingFrame);
    void SetIcon(QImage *spritesheetImage);

    Frame *GetFrame();

    void DestroyFrame();
};

#endif // FRAMELISTITEM_H
