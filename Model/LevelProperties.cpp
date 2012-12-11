#include "LevelProperties.h"

LevelProperties::LevelProperties()
{
    tileWidth = 16;
    tileHeight = 16;
    mapWidth  = 99;
    mapHeight = 99;
    tilesetID = 0;

    levelName = "";
}

bool LevelProperties::IsPropertiesSet()
{
    if(tileWidth && tileHeight && mapWidth && mapHeight)
        return true;

    return false;
}

bool LevelProperties::SaveToFile(Exporter *exporter)
{
    return false;
}

bool LevelProperties::LoadFromFile(Exporter *exporter)
{
    return false;
}
