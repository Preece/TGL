#include "LayerManager.h"

LayerManager::LayerManager()
{
    resourceManager = NULL;
    currentTile = NULL;
    currentLayer = NULL;
    currentBrush = NULL;

    grid = new QGraphicsItemGroup;
    addItem(grid);
    grid->setPos(0, 0);
    grid->hide();
}

LayerManager::~LayerManager()
{
}

void LayerManager::EyedropTile(QPoint pos)
{
    if(!resourceManager || !currentLayer)
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

        emit SelectNewTile(currentLayer->GetTileType(tileX, tileY));
    }
}

void LayerManager::AddLayer(Layer *newLayer)
{
    //create a layer group, and assign the new layer
    TileLayer *tempLayerGroup = new TileLayer;
    tempLayerGroup->SetLayer(newLayer);
    tempLayerGroup->RegisterResourceManager(resourceManager);
    tempLayerGroup->SetLayerSize(resourceManager->GetLevelProperties()->GetMapWidth(),
                                 resourceManager->GetLevelProperties()->GetMapHeight());

    //put the layer group into the list
    layers.insert(0, tempLayerGroup);
    addItem(tempLayerGroup);
    setSceneRect(tempLayerGroup->rect());

    tempLayerGroup->show();
    tempLayerGroup->setPos(0,0);
}

void LayerManager::RemoveLayer(Layer *dirtyLayer)
{
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayer() == dirtyLayer)
        {
            resourceManager->DeleteLayer(layers[i]->GetLayer()->GetID());

            layers[i]->DestroyAllItems();
            delete layers[i];
            layers.removeAt(i);
        }
    }
}

bool LayerManager::IsLayerSelected()
{
    if(currentLayer == NULL)
        return false;

    return true;
}

TileLayer *LayerManager::GetSelectedLayer()
{
    return currentLayer;
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

void LayerManager::SetBrush(TileBrush *newBrush)
{
    if(currentLayer)
        currentLayer->ClearPreview();

    currentBrush = newBrush;
}

void LayerManager::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    QGraphicsScene::mousePressEvent(event);

    if(!currentLayer || !currentBrush)
        return;

    //translate the position to tile coordinates
    int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
    int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    if(event->button() == Qt::LeftButton && !IsObjectSelected())
    {
        resourceManager->BeginUndoOperation("Painting Tiles");

        currentBrush->Press(tileX, tileY, currentLayer);
    }
    else if(event->button() == Qt::RightButton)
    {
        EyedropTile(event->scenePos().toPoint());
        currentBrush->Paint(tileX, tileY, currentLayer, true);
    }
}

void LayerManager::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
    QGraphicsScene::mouseMoveEvent(event);

    if(!currentLayer || !currentBrush)
        return;

    //translate the position to tile coordinates
    int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
    int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    //if the left button is down
    if(event->buttons() == Qt::LeftButton && !IsObjectSelected())
    {
        currentBrush->Move(tileX, tileY, currentLayer, true);
    }
    //if the left mouse button was not down
    else if(currentLayer&& !IsObjectSelected())
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
    int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
    int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    if(event->button() == Qt::LeftButton && !IsObjectSelected())
    {
        resourceManager->EndUndoOperation();
        currentBrush->Release(tileX, tileY, currentLayer);
        currentLayer->RepopulateTiles();
    }
}

void LayerManager::SetLayerSelection(int newSelection)
{
    if(newSelection < 0 || newSelection > layers.count())
    {
        currentLayer = NULL;
        return;
    }

    currentLayer = layers[newSelection];
}

QString LayerManager::GetLayerName(int index)
{
    if(index < 0 || index >= layers.count())
        return QString("Invalid index");

    return resourceManager->GetLayerByIndex(index)->GetName();
}

void LayerManager::UpdateLayerOpacity(Layer *opaqueLayer)
{
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayer() == opaqueLayer)
        {
            qreal opacity = opaqueLayer->GetOpacity();
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

int LayerManager::GetSelectedTileID()
{
    if(currentTile)
        return currentTile->GetTileID();

    return 0;
}

bool LayerManager::IsObjectSelected()
{
    if(this->selectedItems().count() > 0)
        return true;

    return false;
}

void LayerManager::RepopulateAllLayers()
{
    for(int i = 0; i < layers.count(); i++)
        layers[i]->RepopulateTiles();
}

