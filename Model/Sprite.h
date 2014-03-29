#ifndef SPRITE_H
#define SPRITE_H

#include <QImage>
#include <QString>
#include <QList>
#include <QStringList>

#include "ItemNode.h"

#include "Animation.h"
#include "Frame.h"
#include "Image.h"

class Sprite : public ItemNode
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "SPRT"; }

    Sprite();

    QString GetName() { return name; }
    void SetName(QString newName) { name = newName; }

    int GetImageID() { return imageID; }
    void SetImageID(int newImageID);

    int GetAnimationCount() { return children.count(); }

    Animation *GetAnimationByIndex(int index);
    Animation *GetAnimation(int animationID);
    void AddAnimation(Animation *newAnimation);
    void DeleteAnimation(int ID);

    QStringList GetAnimationNames();

    void DestroyAllAnimations();

private:
    QString name;
    int imageID;
};

#endif
