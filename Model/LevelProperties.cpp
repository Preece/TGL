#include "LevelProperties.h"

LevelProperties::LevelProperties()
{
    AddProperty("name", QVariant("New Level"));
    AddProperty("tileWidth", QVariant(16));
    AddProperty("tileHeight", QVariant(16));
    AddProperty("tilesetID", QVariant(0));
}

void LevelProperties::SetTileSize(int newW, int newH)
{
    SetProperty("tileWidth", QVariant(newW));
    SetProperty("tileHeight", QVariant(newH));
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
    SetProperty("name", QVariant(newName));
}

QString LevelProperties::GetLevelName()
{
    return GetProperty("name").toString();
}

void LevelProperties::SetTilesetID(int newID)
{
    SetProperty("tilesetID", QVariant(newID));
}

int LevelProperties::GetTilesetID()
{
    return GetProperty("tilesetID").toInt();
}
