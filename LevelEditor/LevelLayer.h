#ifndef LEVELLAYER_H
#define LEVELLAYER_H

#include <QGraphicsItemGroup>

#include "../Model/ObjectPrototype.h"
#include "../Model/ResourceManager.h"
#include "TileItem.h"

class LevelLayer : public QGraphicsItemGroup
{
private:
    int verticalParallax, horizontalParallax;
    QString name;

public:
    LevelLayer();


};

#endif // LEVELLAYER_H
