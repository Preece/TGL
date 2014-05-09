#ifndef LEVELPROPERTIES_H
#define LEVELPROPERTIES_H

#include <QString>

#include "ItemNode.h"

class LevelProperties : public ObjectNode
{

public:
    LevelProperties();

    void SetTileSize(int newW, int newH);
    int GetTileWidth();
    int GetTileHeight();

    void SetLevelName(QString newName);
    QString GetLevelName();

    void SetTilesetID(int newID);
    int GetTilesetID();

private:
    int tilesetID;
};

#endif // LEVELPROPERTIES_H
