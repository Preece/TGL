#include "LevelProperties.h"

LevelProperties::LevelProperties()
{
    AddProperty("Name", QVariant("New Level"));
    AddProperty("Tile Size", QPoint(16, 16));

    tilesetID = 0;
}

void LevelProperties::SetTileSize(int newW, int newH)
{
    SetProperty("Tile Size", QPoint(newW, newH));
}

int LevelProperties::GetTileWidth()
{
    return GetProperty("Tile Size").toPoint().x();
}

int LevelProperties::GetTileHeight()
{
    return GetProperty("Tile Size").toPoint().y();
}

void LevelProperties::SetLevelName(QString newName)
{
    SetProperty("Name", QVariant(newName));
}

QString LevelProperties::GetLevelName()
{
    return GetProperty("Name").toString();
}

void LevelProperties::SetTilesetID(int newID)
{
    tilesetID = newID;
}

int LevelProperties::GetTilesetID()
{
    return tilesetID;
}
