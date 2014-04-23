#include "LayerManager.h"

LayerManager::LayerManager()
{
    resourceManager = NULL;
    currentLayer = NULL;
    currentBrush = NULL;

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
    if(tileX >= resourceManager->GetMapWidth() || tileY >= resourceManager->GetMapHeight())
        return;

    emit SelectNewTile(currentLayer->GetTileOrigin(tileX, tileY));

    RefreshPreview();
}

void LayerManager::AddLayer(int newLayerID)
{
    //create a layer group, and assign the new layer
    TileLayerView *tempLayerView = new TileLayerView;
    tempLayerView->SetLayerID(newLayerID);
    tempLayerView->RegisterResourceManager(resourceManager);
    tempLayerView->SetLayerSize(resourceManager->GetMapWidth(),
                                 resourceManager->GetMapHeight());

    //put the layer group into the list
    layers.insert(0, tempLayerView);
    addItem(tempLayerView);
    UpdateLayerOpacity(newLayerID);

    tempLayerView->show();
    tempLayerView->setPos(0,0);
    
    setSceneRect(0, 0, resourceManager->GetMapWidth() * resourceManager->GetTileWidth(),
                       resourceManager->GetMapHeight() * resourceManager->GetTileHeight());
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

    if(resourceManager->GetLevelProperties()->ArePropertiesSet())
    {
        QPen pen(Qt::DashLine);
        pen.setColor(QColor(Qt::gray));

        QGraphicsLineItem *tempLine;

        int tileW = resourceManager->GetTileWidth();
        int tileH = resourceManager->GetTileHeight();
        int mapH = resourceManager->GetMapHeight();
        int mapW = resourceManager->GetMapWidth();

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

void LayerManager::SetBrushSelection(TileBrush *newBrush, QCursor newCursor)
{
    if(currentLayer)
        currentLayer->ClearPreview();

    currentBrush = newBrush;
}

void LayerManager::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    if(!currentLayer || !currentBrush)
        return;

    //translate the position to tile coordinates
    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    if(event->button() == Qt::LeftButton)
    {
        currentBrush->Press(tileX, tileY, currentLayer);
    }
    else if(event->button() == Qt::RightButton)
    {
        EyedropTile(event->scenePos().toPoint());

        //refresh the preview
        currentBrush->Paint(tileX, tileY, currentLayer, true);
    }
}

void LayerManager::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    if(!currentLayer || !currentBrush)
        return;

    //translate the position to tile coordinates
    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    lastPreviewSpot.setX(tileX);
    lastPreviewSpot.setY(tileY);

    //if the left button is down
    if(event->buttons() == Qt::LeftButton)
    {
        currentBrush->Move(tileX, tileY, currentLayer, true);
    }
    //if the left mouse button was not down
    else if(currentLayer)
    {
        currentBrush->Move(tileX, tileY, currentLayer, false);
    }
}

void LayerManager::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);

    if(!currentLayer || !currentBrush)
        return;

    //translate the position to tile coordinates
    int tileW = resourceManager->GetTileWidth();
    int tileH = resourceManager->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    if(event->button() == Qt::LeftButton)
    {    
        currentBrush->Release(tileX, tileY, currentLayer);

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

void LayerManager::RefreshPreview()
{
    currentBrush->Paint(lastPreviewSpot.x(), lastPreviewSpot.y(), currentLayer, true);
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

void LayerManager::ClearPreview()
{
    if(currentLayer)
        currentLayer->ClearPreview();
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

void LayerManager::RepopulateAllLayers()
{
    for(int i = 0; i < layers.count(); i++)
        layers[i]->RepopulateTiles();
}

void LayerManager::UpdateLayerSizes(int newW, int newH)
{
    //loop through each layer and modify their sizes
    for(int i = 0; i < layers.count(); i++)
        layers[i]->SetLayerSize(newW, newH);
}