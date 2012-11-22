#ifndef SAVABLE_H
#define SAVABLE_H

#include <QFile>

class Savable
{
protected:
    int ID;

    static int newID;

    int GenerateID();

    //this is used when loading a file. It will make sure the new
    //ID's generated don't conflict with existing ones. All loaded
    //objects should register their ID's.
    void RegisterID(int registeredID);

public:
    Savable();

    int GetID() { return ID; }

    virtual bool SaveToFile(QFile &file) = 0;
    virtual bool LoadFromFile(QFile &file) = 0;


};

#endif // SAVABLE_H
