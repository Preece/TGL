#include "AnimationPreviewer.h"
#include "ui_AnimationPreviewer.h"

AnimationPreviewer::AnimationPreviewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationPreviewer)
{
    ui->setupUi(this);

    connect(ui->playButton, SIGNAL(clicked()), ui->animationLabel, SLOT(Play()));
    connect(ui->pauseButton, SIGNAL(clicked()), ui->animationLabel, SLOT(Pause()));
    connect(ui->nextFrameButton, SIGNAL(clicked()), ui->animationLabel, SLOT(NextFrame()));
    connect(ui->previousFrameButton, SIGNAL(clicked()), ui->animationLabel, SLOT(PrevFrame()));

    connect(this, SIGNAL(finished(int)), ui->animationLabel, SLOT(Pause()));

    connect(ui->animationLabel, SIGNAL(FrameChanged(int)), this, SLOT(UpdateFrameDelay(int)));

    currentAnimation = 0;
}

AnimationPreviewer::~AnimationPreviewer()
{
    delete ui;
}

void AnimationPreviewer::Load(QPixmap *spritesheet, Animation *anim)
{
    currentAnimation = anim;
    ui->animationLabel->LoadAnimation(anim, spritesheet);
}

void AnimationPreviewer::UpdateFrameDelay(int frameIndex)
{
    if(currentAnimation)
        ui->frameDelayInput->setValue(currentAnimation->GetFrameAtIndex(frameIndex)->GetDelay());
}

void AnimationPreviewer::on_frameDelayInput_valueChanged(int arg1)
{
    if(ui->animationLabel->IsAnimationLoaded())
    {
        currentAnimation->GetFrameAtIndex(ui->animationLabel->GetCurrentFrameIndex())->SetDelay(arg1);
    }
}
