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
}

LayerManager::~LayerManager()
{
    //fine-tune this value for optimal performance. 0 is the default,
    //and Qt will try to automatically find a good value. 10 seems to
    //crash the application
    setBspTreeDepth(5);
}

void LayerManager::EyedropTile(QPoint pos)
{
    if(!resourceManager || !currentLayer)
        return;

    if(resourceManager->GetLevelProperties()->ArePropertiesSet())
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

        emit SelectNewTile(currentLayer->GetTileOrigin(tileX, tileY));
    }
}

void LayerManager::AddLayer(TileLayer *newLayer)
{
    //create a layer group, and assign the new layer
    TileLayerView *tempLayerGroup = new TileLayerView;
    tempLayerGroup->SetLayer(newLayer);
    tempLayerGroup->RegisterResourceManager(resourceManager);
    tempLayerGroup->SetLayerSize(resourceManager->GetLevelProperties()->GetMapWidth(),
                                 resourceManager->GetLevelProperties()->GetMapHeight());

    //put the layer group into the list
    layers.insert(0, tempLayerGroup);
    addItem(tempLayerGroup);
    UpdateLayerOpacity(newLayer);

    tempLayerGroup->show();
    tempLayerGroup->setPos(0,0);
    
    setSceneRect(0, 0, resourceManager->GetLevelProperties()->GetMapWidth() * resourceManager->GetLevelProperties()->GetTileWidth(),
                       resourceManager->GetLevelProperties()->GetMapHeight() * resourceManager->GetLevelProperties()->GetTileHeight());
}

void LayerManager::RemoveLayer(TileLayer *dirtyLayer)
{
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayer() == dirtyLayer)
        {
            resourceManager->DeleteTileLayer(layers[i]->GetLayer()->GetID());

            layers[i]->DestroyAllItems();
            delete layers[i];
            layers.removeAt(i);
            currentLayer = NULL;
        }
    }
}

bool LayerManager::IsLayerSelected()
{
    if(currentLayer == NULL)
        return false;

    return true;
}

TileLayerView *LayerManager::GetSelectedLayer()
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

    if(resourceManager->GetLevelProperties()->ArePropertiesSet())
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

    if(event->button() == Qt::LeftButton)
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
    int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
    int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    if(event->button() == Qt::LeftButton)
    {
        resourceManager->EndUndoOperation();
        currentBrush->Release(tileX, tileY, currentLayer);
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

QString LayerManager::GetLayerName(int index)
{
    if(index < 0 || index >= layers.count())
        return QString("Invalid index");

    return resourceManager->GetLayerByIndex(index)->GetName();
}

void LayerManager::UpdateLayerOpacity(TileLayer *opaqueLayer)
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

void LayerManager::RepopulateAllLayers()
{
    for(int i = 0; i < layers.count(); i++)
        layers[i]->RepopulateTiles();
}

