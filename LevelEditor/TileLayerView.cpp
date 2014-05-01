#include "TileLayerView.h"

TileLayerView::TileLayerView()
{
    resourceManager = NULL;
    layerID = 0;
}

TileLayerView::~TileLayerView()
{
    DestroyAllItems();
}

void TileLayerView::ToggleVisibility(bool visible)
{
    if(visible)
        show();
    else
        hide();
}

void TileLayerView::DestroyAllItems()
{
    QList<QGraphicsItem*> children = this->children();

    for(int i = 0; i < children.count(); i++)
    {
        if(children[i])
            delete children[i];
    }

    items.clear();
}

void TileLayerView::SelectTilesInArea(QRect area)
{
    //translate the position to pixel coordinates
    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();

    QPainterPath path;
    path.addRect((area.left() * tileW) + 1, (area.top() * tileH) + 1, (area.width() * tileW) - 2, (area.height() * tileH) - 2);
    scene()->setSelectionArea(path);
}

void TileLayerView::ModifyTileItem(int x, int y, TileCoord newOrigin)
{
    TileCoord tilePos(x, y);

    //first check that this is not a redundant move
    if(items.contains(tilePos))
        if(items[tilePos]->GetTileOrigin() == newOrigin)
            return;


    //then clear out any tile that already exists at this position
    if(items.contains(tilePos))
    {
        scene()->removeItem(items[tilePos]);
        delete items[tilePos];
        items.remove(tilePos);
    }

    //if they are deleting a tile, we can simply leave at this point
    if(newOrigin == TileCoord(-1, -1))
        return;

    TileWidgetItem *tempTileItem = new TileWidgetItem;

    //store the tile origin coordinates in the item
    tempTileItem->SetTileOrigin(newOrigin);
    tempTileItem->SetPosition(tilePos);
    tempTileItem->setFlag(QGraphicsItem::ItemIsSelectable);

    //update its Pixmap
    tempTileItem->SetTilePixmap(resourceManager->GetTilePixmap(newOrigin));

    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();

    //set the position
    tempTileItem->setPos(x * tileW, y * tileH);

    //put the new tile item into the map, with the position as the key
    items[tilePos] = tempTileItem;
    tempTileItem->setParentItem(this);
}
