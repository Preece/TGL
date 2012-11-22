#ifndef ANIMATIONEDIT_H
#define ANIMATIONEDIT_H

#include <QDialog>

#include "Model/Sprite.h"
#include "Model/Animation.h"

namespace Ui {
class AnimationEditor;
}

class AnimationEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit AnimationEditor(QWidget *parent = 0);
    ~AnimationEditor();

    void ClearAll();

public slots:
    void NewAnimation(Animation *newAnimation);
    void EditAnimation(Animation *editAnimation);
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::AnimationEditor *ui;

    Animation *currentAnimation;
};

#endif // ANIMATIONEDIT_H
