#include "TileSelectorScene.h"

TileSelectorScene::TileSelectorScene(QObject *parent)
{
}

void TileSelectorScene::SelectNewTile(TileCoord origin)
{
    int tileW = resources->GetLevelProperties()->GetTileWidth();
    int tileH = resources->GetLevelProperties()->GetTileHeight();

    //find the x and y position of the tile
    int tileX = (tileW * origin.first) + tileW - 1;
    int tileY = (tileH * origin.second) + tileH - 1;

    clearSelection();

    //find that tile based on position
    QGraphicsItem *tempTileItem = itemAt(tileX, tileY);

    //select the new tile
    if(tempTileItem)
        tempTileItem->setSelected(true);
}

TileCoordList TileSelectorScene::GetAllSelectedTiles()
{
    TileCoordList coordList;
    
    //pull out a list of all selected items
    QList<QGraphicsItem*> selectedItems = selectedItems();
    
    //for every one
    for(int i = 0; i < selectedItems.count(); i++)
    {
        //cast it into a tilewidget item
        TileWidgetItem *tempItem = dynamic_cast<TileWidgetItem*>(selectedItems()[i]);
        
        //and add its origin coordinates to the list
        if(tempItem)
            coordList.push_back(tempItem->GetTileOrigin());
    }

    return coordList;
}
