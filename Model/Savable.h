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

    //these functions help write out different types of data
    bool WriteString(QFile &file, QString string);
    bool WriteInt(QFile &file, int number);
    bool WriteBool(QFile &file, bool boolean);
    bool WriteRect(QFile &file, QRect rect);
    bool WritePoint(QFile &file, QPoint point);
    bool WriteImage(QFile &file, QImage image);

    //these functions help read in different types of data
    bool ReadString(QFile &file, QString &string);
    bool ReadInt(QFile &file, int &number);
    bool ReadBool(QFile &file, bool &boolean);
    bool ReadRect(QFile &file, QRect &rect);
    bool ReadPoint(QFile &file, QPoint &point);
    bool ReadImage(QFile &file, QImage &image);


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
