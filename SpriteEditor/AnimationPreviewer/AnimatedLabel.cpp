#include "AnimatedLabel.h"

AnimatedLabel::AnimatedLabel(QWidget *parent) :
    QLabel(parent)
{
    currentAnimation = 0;
    currentImage = 0;
    currentFrame = 0;

    playing = true;

    //advance the frame when the timer expires
    connect(&frameTimer, SIGNAL(timeout()), this, SLOT(AdvanceFrame()));

    frameTimer.start(100);
}

void AnimatedLabel::LoadAnimation(Animation *newAnimation, QPixmap *spritesheet)
{
    currentAnimation = newAnimation;
    currentImage = &spritesheet->toImage();
    playing = true;

    SetupFramePixmaps();
}

bool AnimatedLabel::IsAnimationLoaded()
{
    if(currentAnimation && currentImage)
        return true;

    return false;
}

void AnimatedLabel::ClearAnimation()
{
    currentAnimation = 0;
    currentImage = 0;
    framePixmaps.clear();
}

void AnimatedLabel::AdvanceFrame()
{
    //check if an animation is loaded and there is at least one frame
    if(IsAnimationLoaded() && framePixmaps.count() > 0)
    {
        //and that the animation is playing
        if(playing)
        {
            //loop the current frame back if it exceeds the number of frames
            if(currentFrame >= framePixmaps.count())
                currentFrame = 0;

            emit FrameChanged(currentFrame);

            //set the pixmap to the correct one in the list
            setPixmap(framePixmaps.at(currentFrame));

            //set the timer to the frame delay specified in the frame
            frameTimer.start(currentAnimation->GetFrameAtIndex(currentFrame)->GetDelay());

            //advance the current frame
            currentFrame++;
        }
    }
}

void AnimatedLabel::NextFrame()
{
    if(IsAnimationLoaded() && framePixmaps.count() > 0)
    {
        if(!playing)
        {
            //advance the current frame
            currentFrame++;

            //loop the current frame back if it exceeds the number of frames
            if(currentFrame >= framePixmaps.count())
                currentFrame = 0;

            //set the pixmap to the correct one in the list
            setPixmap(framePixmaps.at(currentFrame));

            emit FrameChanged(currentFrame);

        }
    }
}

void AnimatedLabel::PrevFrame()
{
    if(IsAnimationLoaded() && framePixmaps.count() > 0)
    {
        if(!playing)
        {
            //advance the current frame
            currentFrame--;

            //loop the current frame back if it exceeds the number of frames
            if(currentFrame < 0)
                currentFrame = (framePixmaps.count() - 1);

            //set the pixmap to the correct one in the list
            setPixmap(framePixmaps.at(currentFrame));

            emit FrameChanged(currentFrame);

        }
    }
}

void AnimatedLabel::SetupFramePixmaps()
{
    //check if an animation is loaded
    if(IsAnimationLoaded())
    {
        QImage newFrame;
        framePixmaps.clear();

        //loop for the number of frames in this animation
        for(int i = 0; i < currentAnimation->GetFrameCount(); i++)
        {
            //cut out a pixmap from the image based on frame data
            newFrame = currentImage->copy(currentAnimation->GetFrameAtIndex(i)->GetFrameRect());

            //add the pixmap to the list
            framePixmaps.append(QPixmap::fromImage(newFrame));
        }
    }
}
