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

bool LevelProperties::ArePropertiesSet()
{
    if(tileWidth && tileHeight && mapWidth && mapHeight)
        return true;

    return false;
}
<<<<<<< HEAD

void LevelProperties::SetMapSize(int newW, int newH)
{ 
    mapWidth = newW;
    mapHeight = newH;
}
