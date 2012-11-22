#include "AnimationEditor.h"
#include "ui_AnimationEditor.h"

AnimationEditor::AnimationEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnimationEditor)
{
    ui->setupUi(this);

    currentAnimation = 0;
}

AnimationEditor::~AnimationEditor()
{
    delete ui;
}

void AnimationEditor::ClearAll()
{
    ui->animationNameInput->clear();
    ui->loopSelector->setChecked(false);
}

void AnimationEditor::NewAnimation(Animation *newAnimation)
{
    ClearAll();
    currentAnimation = newAnimation;
}

void AnimationEditor::EditAnimation(Animation *editAnimation)
{
    ClearAll();
    currentAnimation = editAnimation;

    ui->animationNameInput->setText(currentAnimation->GetName());
    ui->loopSelector->setChecked(currentAnimation->GetLoop());
}

void AnimationEditor::on_buttonBox_accepted()
{
    if(ui->animationNameInput->text() == "")
        currentAnimation->SetName("New Animation");
    else
        //set the current animations name
        currentAnimation->SetName(ui->animationNameInput->text());

    currentAnimation->SetLoop(ui->loopSelector->isChecked());
}
