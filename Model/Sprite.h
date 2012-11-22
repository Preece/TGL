#ifndef SPRITE_H
#define SPRITE_H

#include <QImage>
#include <QString>
#include <QList>
#include <QStringList>

#include "savable.h"

#include "Animation.h"
#include "Frame.h"
#include "Image.h"

class Sprite : public Savable
{
private:
    QString name;

    int imageID;
    QList<Animation*> animations;
public:
    bool SaveToFile(QFile &file);
    bool LoadFromFile(QFile &file);

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    int GetImageID() { return imageID; }
    void SetImageID(int newImageID);

    Animation *GetAnimation(int animationID);
    void AddAnimation(Animation *newAnimation);

    QStringList GetAnimationNames();

    void DestroyAllAnimations();

};

#endif
