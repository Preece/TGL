#include "LayerManager.h"

LayerManager::LayerManager()
{
    resourceManager = NULL;
    currentLayer = NULL;
    brushManager = NULL;

    grid = new QGraphicsItemGroup;
    addItem(grid);
    grid->setPos(0, 0);
    grid->hide();

    setSceneRect(0, 0, 0, 0);
    setItemIndexMethod(NoIndex);
}

LayerManager::~LayerManager()
{
}

void LayerManager::EyedropTile(QPoint pos)
{
    if(!resourceManager || !currentLayer)
        return;

    //translate the position to tile coordinates
    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();

    int tileX = pos.x() / tileW;
    int tileY = pos.y() / tileH;

    //if the position is beyond the bounds of the scene, ignore it
    //EVENTUALLY THE PARALLAX WILL NEED TO BE CONSIDERED
    if(tileX >= resourceManager->GetCurrentLayerWidth() || tileY >= resourceManager->GetCurrentLayerHeight())
        return;

    emit SelectNewTile(resourceManager->GetTileOrigin(tileX, tileY));

    RefreshPreview();
}

void LayerManager::AddLayer(int newLayerID)
{
    //create a layer group, and assign the new layer
    TileLayerView *tempLayerView = new TileLayerView;
    tempLayerView->SetLayerID(newLayerID);
    tempLayerView->RegisterResourceManager(resourceManager);

    //put the layer group into the list
    layers.insert(0, tempLayerView);
    addItem(tempLayerView);
    UpdateLayerOpacity(newLayerID);

    tempLayerView->show();
    tempLayerView->setPos(0,0);
    
    setSceneRect(0, 0, resourceManager->GetCurrentLayerWidth() * resourceManager->GetTileWidth(),
                       resourceManager->GetCurrentLayerHeight() * resourceManager->GetTileHeight());
}

void LayerManager::UpdateSceneSize(int w, int h)
{
    int newW, newH;

    if(w * resourceManager->GetTileWidth() > sceneRect().width())
        newW = w * resourceManager->GetTileWidth();

    if(h * resourceManager->GetTileHeight() > sceneRect().height())
        newH = h * resourceManager->GetTileHeight();

    //the scene rect should always be as big as the biggest layer
    setSceneRect(0, 0, newW, newH);
}

void LayerManager::RemoveLayer(int dirtyLayerID)
{
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayerID() == dirtyLayerID)
        {
            resourceManager->DeleteTileLayer(layers[i]->GetLayerID());

            layers[i]->DestroyAllItems();
            delete layers[i];
            layers.removeAt(i);
            currentLayer = NULL;
        }
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

    QPen pen(Qt::DashLine);
    pen.setColor(QColor(Qt::gray));

    QGraphicsLineItem *tempLine;

    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();
    int mapH = resourceManager->GetCurrentLayerHeight();
    int mapW = resourceManager->GetCurrentLayerWidth();

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

void LayerManager::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!currentLayer)
        return;

    //translate the position to tile coordinates
    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    if(event->button() == Qt::LeftButton)
    {
        brushManager->GetCurrentBrush()->Press(tileX, tileY, resourceManager);
    }
    else if(event->button() == Qt::RightButton)
    {
        EyedropTile(event->scenePos().toPoint());

        //refresh the preview
        brushManager->GetCurrentBrush()->Paint(tileX, tileY, resourceManager, true);
    }
}

void LayerManager::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!currentLayer)
        return;

    //translate the position to tile coordinates
    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    //do not send duplicate events
    if(lastPreviewSpot.x() == tileX && lastPreviewSpot.y() == tileY)
        return;
    
    lastPreviewSpot.setX(tileX);
    lastPreviewSpot.setY(tileY);

    //if the left button is down
    if(event->buttons() == Qt::LeftButton)
    {
        brushManager->GetCurrentBrush()->Move(tileX, tileY, resourceManager, true);
    }
    //if the left mouse button was not down
    else if(currentLayer)
    {
        brushManager->GetCurrentBrush()->Move(tileX, tileY, resourceManager, false);
    }
}

void LayerManager::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!currentLayer)
        return;

    //translate the position to tile coordinates
    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    if(event->button() == Qt::LeftButton)
    {    
        brushManager->GetCurrentBrush()->Release(tileX, tileY, resourceManager);

        //this will package the changes into an undo command and implement them into the model
        //make it abort if the queue is empty
        resourceManager->EndPaintOperation();
    }
}

void LayerManager::SetLayerSelection(int newSelection)
{
    //loop through all the layers
    for(int i = 0; i < layers.count(); i++)
    {
        //and if there is a layer associated with the correct ID, set it as the current layer
        if(layers[i]->GetLayerID() == newSelection)
        {
            currentLayer = layers[i];
            return;
        }
    }

    //if it was not found, just NULL out the current layer. Checks elsewhere will prevent drawing
    currentLayer = NULL;
}

void LayerManager::UpdateLayerVisibility(int ID, bool visible)
{
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayerID() == ID)
            layers[i]->setVisible(visible);
    }
}

void LayerManager::RefreshPreview()
{
    ClearPreview();
    brushManager->GetCurrentBrush()->Paint(lastPreviewSpot.x(), lastPreviewSpot.y(), resourceManager, true);
}

void LayerManager::ClearPreview()
{
    if(brushManager->GetCurrentBrush()->GetType() != "selector")
        resourceManager->ClearPreview();

    ClearEraserPreview();
}

void LayerManager::SelectPreviewItems()
{
    QList<TileWidgetItem*> tileList = previewItems.values();

    for(int i = 0; i < tileList.count(); i++)
    {
        if(tileList[i])
            tileList[i]->setSelected(true);
    }
}

void LayerManager::UpdateLayerOpacity(int opaqueLayerID)
{
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayerID() == opaqueLayerID)
        {
            qreal opacity = resourceManager->GetLayerOpacity(opaqueLayerID);
            opacity = opacity / 100;
            layers[i]->setOpacity(opacity);
        }
    }
}

void LayerManager::ToggleLayerVisibility(int layerIndex, bool show)
{
    if(layerIndex < 0 || layerIndex >= layers.count())
        return;

    layers[layerIndex]->ToggleVisibility(show);
}

void LayerManager::ToggleSelectionMode(bool selection)
{
    QList<QGraphicsItem*> childrenList = items();

    //make every current item selectable
    if(selection)
    {
        for(int i = 0; i < childrenList.count(); i++)
            childrenList[i]->setFlag(QGraphicsItem::ItemIsSelectable);

        resourceManager->EndPaintOperation();
    }
    //make all items non-selectable
    else
    {
        for(int i = 0; i < childrenList.count(); i++)
            childrenList[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);

        ClearPreview();
    }
}

void LayerManager::UpdateTile(int layerID, int x, int y, TileCoord newOrigin)
{
    //the layers should potentially be stored in a hash,
    //to avoid this looping for every single tile
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayerID() == layerID)
        {
            layers[i]->ModifyTileItem(x, y, newOrigin);
            return;
        }
    }
}

void LayerManager::UpdatePreviewTile(int x, int y, TileCoord origin)
{
    //bounds check
    if(x >= resourceManager->GetCurrentLayerWidth() || y >= resourceManager->GetCurrentLayerHeight() || x < 0 || y < 0)
        return;

    if(origin == TileCoord(-1, -1))
    {
        if(previewItems.contains(TileCoord(x, y)))
        {
            removeItem(previewItems[TileCoord(x, y)]);
            delete previewItems[TileCoord(x, y)];
            previewItems.remove(TileCoord(x, y));
            return;
        }
    }

    TileWidgetItem *tempTile = new TileWidgetItem;
    tempTile->setFlag(QGraphicsItem::ItemIsSelectable);

    //update its Pixmap
    tempTile->SetTilePixmap(resourceManager->GetTilePixmap(origin));

    //set the position
    tempTile->setPos(x * resourceManager->GetTileWidth(),
                     y * resourceManager->GetTileHeight());

    previewItems[TileCoord(x, y)] = tempTile;
    addItem(tempTile);
}

void LayerManager::UpdateSelectionGeometry(QRect rect)
{
    if(currentLayer)
        currentLayer->SelectTilesInArea(rect);
}

void LayerManager::DrawEraserPreview(int x, int y)
{
    QGraphicsRectItem *rect = new QGraphicsRectItem(x * resourceManager->GetTileWidth(),
                           y * resourceManager->GetTileHeight(),
                           resourceManager->GetTileWidth(),
                           resourceManager->GetTileHeight());

    rect->setBrush(QBrush(QColor(0, 0, 255, 0x80)));
    rect->setPen(QPen(Qt::transparent));

    addItem(rect);
    eraserPreviewItems.append(rect);
}

void LayerManager::ClearEraserPreview()
{
    for(int i = 0; i < eraserPreviewItems.count(); i++)
    {
        removeItem(eraserPreviewItems[i]);
        delete eraserPreviewItems[i];
        eraserPreviewItems[i] = NULL;
    }

    eraserPreviewItems.clear();
}
