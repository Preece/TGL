#include "TileSelectorScene.h"

TileSelectorScene::TileSelectorScene(QObject *parent)
{
    connect(this, SIGNAL(selectionChanged()), this, SLOT(PackageAndEmitSelection()));

    selection = new QRubberBand(QRubberBand::Rectangle);

    QPalette palette;
    palette.setBrush(QPalette::Foreground, QBrush(Qt::green));
    palette.setBrush(QPalette::Base, QBrush(Qt::red));

    selection->setPalette(palette);
}

TileSelectorScene::~TileSelectorScene()
{
    delete selection;
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
                    tempItem->SetTileOrigin(TileCoord(j, i));

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
    int tileX = (tileW * origin.x) + tileW - 1;
    int tileY = (tileH * origin.y) + tileH - 1;

    clearSelection();

    if(origin.x == -1 && origin.y == -1)
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

void TileSelectorScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        clickSpot = event->scenePos().toPoint();
    }
}

void TileSelectorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if(event->buttons() & Qt::LeftButton)
    {
        selection->setGeometry(clickSpot.x(), clickSpot.y(),
                               event->scenePos().x() - clickSpot.x(), event->scenePos().y() - clickSpot.y());

        QPainterPath path;
        path.addRect(clickSpot.x(), clickSpot.y(),
                     event->scenePos().x() - clickSpot.x(), event->scenePos().y() - clickSpot.y());

        setSelectionArea(path);
    }
}

void TileSelectorScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if(event->button() == Qt::LeftButton)
    {
        selection->setGeometry(0, 0, 0, 0);
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
