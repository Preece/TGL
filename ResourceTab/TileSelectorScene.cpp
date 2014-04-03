#include "TileSelectorScene.h"

TileSelectorScene::TileSelectorScene(QObject *parent)
{
    connect(this, SIGNAL(selectionChanged()), this, SLOT(PackageAndEmitSelection()));
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

    //if the origin is -1, -1
        //somehow select the eraser tool, they eyedropped a blank spot

}

TileList TileSelectorScene::GetSelectedTiles()
{
    TileList coordList;
    
    //pull out a list of all selected items
    QList<QGraphicsItem*> selectedTiles = selectedItems();
    
    //for every one
    for(int i = 0; i < selectedTiles.count(); i++)
    {
        //cast it into a tilewidget item
        TileWidgetItem *tempItem = dynamic_cast<TileWidgetItem*>(selectedTiles[i]);
        
        //and add its origin coordinates to the list
        if(tempItem)
            coordList.push_back(tempItem->GetTileOrigin());
    }

    return coordList;
}

void TileSelectorScene::PackageAndEmitSelection()
{
    emit SelectionChanged(GetSelectedTiles());
}
