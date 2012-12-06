#include "LevelProperties.h"

LevelProperties::LevelProperties()
{
    tileWidth = 0;
    tileHeight = 0;
    mapWidth  = 0;
    mapHeight = 0;
    tilesetID = 0;

    levelName = "";
}

bool LevelProperties::IsPropertiesSet()
{
    if(tileWidth && tileHeight && mapWidth && mapHeight)
        return true;

    return false;
}

bool LevelProperties::SaveToFile(QFile &file)
{
    return false;
}

bool LevelProperties::LoadFromFile(QFile &file)
{
    return false;
}
