#include "LayerManager.h"

LayerManager::LayerManager()
{
    resourceManager = NULL;
    currentTile = NULL;
    scaffold = new LevelLayer;

    addItem(scaffold);
    scaffold->setPos(0, 0);
    scaffold->show();
}

LayerManager::~LayerManager()
{
    delete scaffold;
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

        //get rid of the tile at that position, if there is one.
        if(itemAt(pos.x(), pos.y()))
            delete itemAt(pos.x(), pos.y());

        //create a new TileItem
        TileItem *tempTile = new TileItem;
        tempTile->SetTile(currentTile->GetTile());

        //set the tile items pixmap and may Jaysus forgive me for this abomination
        tempTile->SetTilePixmap(*resourceManager->GetTileset(), currentTile->GetTile()->GetXOrigin(), currentTile->GetTile()->GetYOrigin(),
                                resourceManager->GetLevelProperties()->GetTileWidth(), resourceManager->GetLevelProperties()->GetTileHeight());

        //add it to the scene
        scaffold->addToGroup(tempTile);

        //set its position
        tempTile->setPos(tileX * tileW, tileY * tileH);
    }
}

void LayerManager::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ModifyTile(event->pos().toPoint());
}
