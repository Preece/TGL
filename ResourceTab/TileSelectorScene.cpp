#include "TileSelectorScene.h"

TileSelectorScene::TileSelectorScene(QObject *parent)
{
    connect(this, SIGNAL(selectionChanged()), this, SLOT(PackageAndEmitSelection()));
}

void TileSelectorScene::RepopulateTileSelector()
{
    clear();

    if(!spritesheet)
        return;

    if(!spritesheet->isNull())
    {
        int tileW = resources->GetLevelProperties()->GetTileWidth();
        int tileH = resources->GetLevelProperties()->GetTileHeight();

        if(tileW && tileH)
        {
            int imageW = spritesheet->width() / tileW;
            int imageH = spritesheet->height() / tileH;

            TileWidgetItem *tempItem;
            Tile *tempTile;

            //loop for the width of the spritesheet divided by the width of a tile
            for(int i = 0; i < imageH; i++)
            {
                //loop for the height of the spritesheet divided by the height of a tile
                for(int j = 0; j < imageW; j++)
                {
                    tempItem = new TileWidgetItem;

                    //copy the correct fragment of the image into a new TileItem
                    tempItem->SetTilePixmap(resources->GetTilePixmap(TileCoord(j, i)));

                    //create a tile with the correct origin points, and add it in.
                    //the x and y are -1 to indicate that this doesnt exist in the tile
                    //grid, only in the selector pane
                    tempTile = new Tile();
                    tempTile->originX = j;
                    tempTile->originY = i;
                    tempTile->x = -1;
                    tempTile->y = -1;
                    tempItem->SetTile(tempTile);

                    //add the tile item to the tile selector at (i * tilewidth) + i
                    addItem(tempItem);

                    tempItem->setPos((j * tileW) + j, (i * tileH) + i);
                    tempItem->setFlag(QGraphicsItem::ItemIsSelectable);
                }
            }
        }
    }
}

void TileSelectorScene::SelectNewTile(TileCoord origin)
{
    int tileW = resources->GetLevelProperties()->GetTileWidth();
    int tileH = resources->GetLevelProperties()->GetTileHeight();

    //find the x and y position of the tile
    int tileX = (tileW * origin.first) + tileW - 1;
    int tileY = (tileH * origin.second) + tileH - 1;

    clearSelection();

    if(origin.first == -1 && origin.second == -1)
    {
        emit SelectEraser();
    }

    //find that tile based on position
    QGraphicsItem *tempTileItem = itemAt(tileX, tileY);

    //select the new tile
    if(tempTileItem)
        tempTileItem->setSelected(true);
}

void TileSelectorScene::SelectTileset()
{
    //bring up an image selection window
    SpritesheetSelector spritesheetWindow;

    spritesheetWindow.RegisterResourceManager(resources);
    spritesheetWindow.RepopulateImageList();

    //if the user completes the dialog
    if(spritesheetWindow.exec() == QDialog::Accepted)
    {
        //and if an image was selected
        if(spritesheetWindow.IsImageSelected() && resources->GetLevelProperties()->ArePropertiesSet())
        {
            //set the spritesheet as that image
            spritesheet = spritesheetWindow.GetSelectedImage()->GetImage();

            //store its ID as the image to be used as the tileset
            resources->GetLevelProperties()->SetTilesetID(spritesheetWindow.GetSelectedImage()->GetID());

            //and repopulate the tile selector
            RepopulateTileSelector();
        }
    }
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
