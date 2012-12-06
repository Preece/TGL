#include "LayerManager.h"

LayerManager::LayerManager()
{
    resourceManager = NULL;
    currentTile = NULL;

    grid = new QGraphicsItemGroup;
    scaffold = new LevelLayer;

    addItem(scaffold);
    scaffold->setPos(0, 0);
    scaffold->show();


    addItem(grid);
    grid->setPos(0, 0);
    grid->hide();
}

LayerManager::~LayerManager()
{
}

void LayerManager::ModifyTile(QPoint pos)
{
    if(!resourceManager || !currentTile)
        return;

    if(resourceManager->GetLevelProperties()->IsPropertiesSet())
    {
        //translate the position to tile coordinates
        int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
        int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

        int tileX = pos.x() / tileW;
        int tileY = pos.y() / tileH;

        //if the position is beyond the bounds of the scene, ignore it
        //EVENTUALLY THE PARALLAX WILL NEED TO BE CONSIDERED
        if(tileX >= resourceManager->GetLevelProperties()->GetMapWidth() ||
           tileY >= resourceManager->GetLevelProperties()->GetMapHeight())
            return;

        TileItem *tempTile;

        //if there is already a tile there, change its stuff

        //create a new TileItem
        tempTile = new TileItem;


        tempTile->SetTile(currentTile->GetTile());

        //set the tile items pixmap and may Jaysus forgive me for this abomination
        tempTile->SetTilePixmap(*resourceManager->GetTileset(), currentTile->GetTile()->GetXOrigin(), currentTile->GetTile()->GetYOrigin(),
                                resourceManager->GetLevelProperties()->GetTileWidth(), resourceManager->GetLevelProperties()->GetTileHeight());

        //add it to the scene
        scaffold->addToGroup(tempTile);

        //set its position
        tempTile->setPos(tileX * tileW, tileY * tileH);

        //modify the model to represent this new tile
    }
}

void LayerManager::ToggleGrid(bool show)
{
    if(show == false)
    {
        grid->hide();
        return;
    }

    if(grid)
    {
        delete grid;
        grid = new QGraphicsItemGroup;
    }

    if(resourceManager->GetLevelProperties()->IsPropertiesSet())
    {
        QPen pen(Qt::DashLine);
        pen.setColor(QColor(Qt::gray));

        QGraphicsLineItem *tempLine;

        int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
        int tileH = resourceManager->GetLevelProperties()->GetTileHeight();
        int mapH = resourceManager->GetLevelProperties()->GetMapHeight();
        int mapW = resourceManager->GetLevelProperties()->GetMapWidth();

        //loop for the height of the map, draw horizontal lines
        for(int i = 1; i < mapH; i++)
        {
            tempLine = new QGraphicsLineItem(0, (i * tileH), (mapW * tileW), (i * tileH));
            tempLine->setPen(pen);
            grid->addToGroup(tempLine);
        }

        //loop for the width of the map, draw vertical lines
        for(int j = 1; j < mapW; j++)
        {
            tempLine = new QGraphicsLineItem((j * tileW), 0, (j * tileW), (mapH * tileH));
            tempLine->setPen(pen);
            grid->addToGroup(tempLine);
        }

        addItem(grid);

        grid->setZValue(99);
        grid->show();
    }
}

void LayerManager::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ModifyTile(event->scenePos().toPoint());
}

void LayerManager::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    ModifyTile(event->scenePos().toPoint());
}
