#include "LayerManager.h"

LayerManager::LayerManager()
{
    resourceManager = NULL;
    currentTile = NULL;
    currentLayer = NULL;
    selectedTool = 0;

    grid = new QGraphicsItemGroup;

    addItem(grid);
    grid->setPos(0, 0);
    grid->hide();
}

LayerManager::~LayerManager()
{
}
void LayerManager::FloodFill(int tileX, int tileY, int newTileID, int oldTileID)
{
   /* //this is a recursive function. It calls itself in tiles to the north, east, south and west.
    //it will return if the tile is different from the one being replaced, or off the edge of the grid

    if(!resourceManager || !currentTile || !currentLayer)
        return;

    if(newTileID == oldTileID)
        return;

    if(resourceManager->GetLevelProperties()->IsPropertiesSet())
    {
        //if the position is beyond the bounds of the scene, ignore it
        //EVENTUALLY THE PARALLAX WILL NEED TO BE CONSIDERED
        if(tileX >= resourceManager->GetLevelProperties()->GetMapWidth() ||
           tileY >= resourceManager->GetLevelProperties()->GetMapHeight() ||
           tileX < 0 || tileY < 0)
            return;

        //modify the correct tiles tileID to the one of the selection
        Layer *currentModelLayer = currentLayer->GetLayer();

        if(currentModelLayer)
        {
            //if the current tile is of the type to be replaced
            if(currentModelLayer->GetTileType(tileX, tileY) == oldTileID)
            {
                //replace this tile with the new type
                ModifyTile(tileX, tileY, false);

                //call this function on the surrounding tiles
                FloodFill(tileX - 1, tileY, newTileID, oldTileID);
                FloodFill(tileX + 1, tileY, newTileID, oldTileID);
                FloodFill(tileX, tileY - 1, newTileID, oldTileID);
                FloodFill(tileX, tileY + 1, newTileID, oldTileID);
            }
        }
    }*/
}

void LayerManager::EraseTile(QPoint pos)
{
   /* if(!resourceManager || !currentTile || !currentLayer)
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

        //modify the correct tiles tileID to the one of the selection
        Layer *currentModelLayer = resourceManager->GetLayer(currentLayer->GetLayerID());

        if(currentModelLayer)
        {
            currentModelLayer->ModifyTile(tileX, tileY, 0);
        }

        RepopulateLayer(currentLayer);
    }*/
}

void LayerManager::EyedropTile(QPoint pos)
{
    /*if(!resourceManager || !currentLayer)
        return;

    if(resourceManager->GetLevelProperties()->IsPropertiesSet())
    {
        //unselect the current tile
        if(currentTile)
            currentTile->setSelected(false);

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

        //modify the correct tiles tileID to the one of the selection
        Layer *currentModelLayer = resourceManager->GetLayer(currentLayer->GetLayerID());

        if(currentModelLayer)
        {
            emit SelectNewTile(currentModelLayer->GetTileType(tileX, tileY));
        }
    }*/
}

void LayerManager::AddLayer(QString name)
{
    //create and add a layer to the resource manager
    Layer *tempLayer = new Layer;
    tempLayer->SetName(name);
    resourceManager->AddLayer(tempLayer);

    //create a layer group, and assign the new layer
    LayerGroup *tempLayerGroup = new LayerGroup;
    tempLayerGroup->SetLayer(tempLayer);
    tempLayerGroup->RegisterResourceManager(resourceManager);
    tempLayerGroup->SetLayerSize(resourceManager->GetLevelProperties()->GetMapWidth(),
                                 resourceManager->GetLevelProperties()->GetMapHeight());

    //put the layer group into the list
    layers.append(tempLayerGroup);
    addItem(tempLayerGroup);

    tempLayerGroup->show();
    tempLayerGroup->setPos(0,0);
}

bool LayerManager::IsLayerSelected()
{
    if(currentLayer == NULL)
        return false;

    return true;
}

LayerGroup *LayerManager::GetSelectedLayer()
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

void LayerManager::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        //pencil
        if(selectedTool == 0)
        {
            //translate the position to tile coordinates
            int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
            int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

            int tileX = event->scenePos().toPoint().x() / tileW;
            int tileY = event->scenePos().toPoint().y() / tileH;

            currentLayer->ModifyTile(tileX, tileY, currentTile->GetTile()->GetID());
        }

        //eyedropper
        if(selectedTool == 1)
        {
            EyedropTile(event->scenePos().toPoint());

            //switch back to the pencil tool
        }

        //bucket
        if(selectedTool == 3)
        {
            /*//translate the position to tile coordinates
            int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
            int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

            int tileX = event->scenePos().toPoint().x() / tileW;
            int tileY = event->scenePos().toPoint().y() / tileH;

            Layer *tempLayer = resourceManager->GetLayer(currentLayer->GetLayerID());
            int oldTileID = tempLayer->GetTileType(tileX, tileY);

            FloodFill(tileX, tileY, currentTile->GetTile()->GetID(), oldTileID);

            RepopulateLayer(currentLayer);*/
        }

        //eraser
        if(selectedTool == 4)
        {
            EraseTile(event->scenePos().toPoint());
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        //pencil, eraser, bucket
        if(selectedTool == 0 || selectedTool == 3 || selectedTool == 4)
        {
            EyedropTile(event->scenePos().toPoint());
        }
    }
}

void LayerManager::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //pencil
    if(selectedTool == 0)
    {
        //translate the position to tile coordinates
        int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
        int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

        int tileX = event->scenePos().toPoint().x() / tileW;
        int tileY = event->scenePos().toPoint().y() / tileH;

        currentLayer->ModifyTile(tileX, tileY, currentTile->GetTile()->GetID());
    }

    //eraser
    if(selectedTool == 4)
        EraseTile(event->scenePos().toPoint());
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

void LayerManager::ToggleLayerVisibility(int layerIndex, bool show)
{
    if(layerIndex < 0 || layerIndex >= layers.count())
        return;

    if(show)
        layers[layerIndex]->show();
    else
        layers[layerIndex]->hide();
}

