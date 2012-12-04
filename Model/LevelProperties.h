#ifndef LEVELPROPERTIES_H
#define LEVELPROPERTIES_H

#include <QString>

class LevelProperties
{
private:
    int tileWidth, tileHeight;
    QString levelName;
    int mapWidth, mapHeight;

    int tilesetID;

public:
    LevelProperties();

    void SetTileSize(int newW, int newH) { tileWidth = newW; tileHeight = newH; }
    void SetTileWidth(int newW) { tileWidth = newW; }
    void SetTileHeight(int newH) { tileHeight = newH; }
    int GetTileWidth() { return tileWidth; }
    int GetTileHeight() { return tileHeight; }

    void SetLevelName(QString newName) { levelName = newName; }
    QString GetLevelName() { return levelName; }

    void SetMapSize(int newW, int newH) { mapWidth = newW; mapHeight = newH; }
    void SetMapWidth(int newW) { mapWidth = newW; }
    void SetMapHeight(int newH) { mapHeight = newH; }
    int GetMapWidth() { return mapWidth; }
    int GetMapHeight() { return mapHeight; }

    void SetTilesetID(int newID) { tilesetID = newID; }
    int GetTilesetID() { return tilesetID; }

    bool IsPropertiesSet();
};

#endif // LEVELPROPERTIES_H
