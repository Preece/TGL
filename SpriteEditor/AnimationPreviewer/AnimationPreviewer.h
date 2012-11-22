#ifndef ANIMATIONPREVIEWER_H
#define ANIMATIONPREVIEWER_H

#include <QDialog>
#include "../../Model/Animation.h"

namespace Ui {
class AnimationPreviewer;
}

class AnimationPreviewer : public QDialog
{
    Q_OBJECT
    
public:
    explicit AnimationPreviewer(QWidget *parent = 0);
    ~AnimationPreviewer();

    void Load(QPixmap *spritesheet, Animation *anim);
    
private:
    Ui::AnimationPreviewer *ui;

    Animation *currentAnimation;

public slots:
    void UpdateFrameDelay(int frameIndex);
private slots:
    void on_frameDelayInput_valueChanged(int arg1);
};

#endif // ANIMATIONPREVIEWER_H
