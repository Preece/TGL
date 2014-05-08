#ifndef LEVELPROPERTIES_H
#define LEVELPROPERTIES_H

#include <QString>

#include "ItemNode.h"

class LevelProperties : public ObjectNode
{

public:
    LevelProperties();

    void SetTileSize(int newW, int newH) { tileWidth = newW; tileHeight = newH; }
    int GetTileWidth() { return tileWidth; }
    int GetTileHeight() { return tileHeight; }

    void SetLevelName(QString newName) { levelName = newName; }
    QString GetLevelName() { return levelName; }

    void SetMapSize(int newW, int newH);
    int GetMapWidth() { return mapWidth; }
    int GetMapHeight() { return mapHeight; }

    void SetTilesetID(int newID) { tilesetID = newID; }
    int GetTilesetID() { return tilesetID; }

    bool ArePropertiesSet();

private:
    int tileWidth, tileHeight;
    int mapWidth, mapHeight;

    QString levelName;

    int tilesetID;
};

#endif // LEVELPROPERTIES_H
