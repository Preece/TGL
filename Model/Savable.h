#ifndef SAVABLE_H
#define SAVABLE_H

#include <QFile>
#include <QRect>
#include <QPoint>
#include <QImage>
#include <QList>

class Savable
{
protected:
    static int newID;

    int ID;
    QList<Savable*> children;

    int GenerateID();

    //this is used when loading a file. It will make sure the new
    //ID's generated don't conflict with existing ones. All loaded
    //objects should register their ID's.
    void RegisterID(int registeredID);

public:
    Savable();

    int GetID() { return ID; }

    virtual QString GetType() = 0;
    virtual bool SaveToFile(QFile &file) = 0;
    virtual bool LoadFromFile(QFile &file) = 0;

    void AddChild(Savable *newChild);
    Savable *GetChild(int ID);
    Savable *GetChildByIndex(int i);
    int GetChildCount();
    void RemoveChild(int ID);


};

#endif // SAVABLE_H
