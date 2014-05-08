#include "LevelProperties.h"

LevelProperties::LevelProperties()
{
    AddProperty("name", QVariant("New Level"));
    AddProperty("tileWidth", 16);
    AddProperty("tileHeight", 16);
    AddProperty("tilesetID", 0);
}

void LevelProperties::SetTileSize(int newW, int newH)
{
    SetProperty("tileWidth", newW);
    SetProperty("tileHeight", newH);
}

int LevelProperties::GetTileWidth()
{
    return GetProperty("tileWidth").toInt();
}

int LevelProperties::GetTileHeight()
{
    return GetProperty("tileHeight").toInt();
}

void LevelProperties::SetLevelName(QString newName)
{
    SetProperty("name", newName);
}

QString LevelProperties::GetLevelName()
{
    GetProperty("name").toString();
}

void LevelProperties::SetTilesetID(int newID)
{
    SetProperty("tilesetID", newID);
}

int LevelProperties::GetTilesetID()
{
    GetProperty("tilesetID").toInt();
}
