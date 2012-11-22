#ifndef ANIMATEDLABEL_H
#define ANIMATEDLABEL_H

#include <QLabel>
#include <QImage>
#include <QTimer>
#include <QPixmap>
#include <QList>

#include "../../Model/Animation.h"

class AnimatedLabel : public QLabel
{
    Q_OBJECT
private:
    Animation *currentAnimation;
    QImage *currentImage;

    QList<QPixmap> framePixmaps;
    void SetupFramePixmaps();

    QTimer frameTimer;
    int currentFrame;

    QImage spritesheetImage;

    bool playing;

public:
    explicit AnimatedLabel(QWidget *parent = 0);

    void LoadAnimation(Animation *newAnimation, QPixmap *spritesheet);
    bool IsAnimationLoaded();
    void ClearAnimation();

    int GetCurrentFrameIndex() { return currentFrame; }
    
signals:
    void FrameChanged(int newFrameIndex);
    
public slots:
    void Play() { playing = true; }
    void Pause() { playing = false; }

    void AdvanceFrame();
    void NextFrame();
    void PrevFrame();
    
};

#endif // ANIMATEDLABEL_H
