#ifndef LEVELPROPERTIES_H
#define LEVELPROPERTIES_H

#include "Savable.h"

#include <QString>

class LevelProperties : public Savable
{
public:
    bool Export(Exporter *exporter);
    bool Import(Exporter *exporter);
    QString GetType() { return "LVLP"; }

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

private:
    int tileWidth, tileHeight;
    QString levelName;
    int mapWidth, mapHeight;

    int tilesetID;
};

#endif // LEVELPROPERTIES_H
