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

void LayerManager::ModifyTile(QPoint pos)
{
    if(!resourceManager || !currentTile || !currentLayer)
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
            currentModelLayer->ModifyTile(tileX, tileY, currentTile->GetTile()->GetID());
        }

        RepopulateLayer(currentLayer);
    }
}

void LayerManager::ModifyTile(int tileX, int tileY, bool repopulate)
{
    if(!resourceManager || !currentTile || !currentLayer)
        return;

    if(resourceManager->GetLevelProperties()->IsPropertiesSet())
    {
        //if the position is beyond the bounds of the scene, ignore it
        //EVENTUALLY THE PARALLAX WILL NEED TO BE CONSIDERED
        if(tileX >= resourceManager->GetLevelProperties()->GetMapWidth() ||
           tileY >= resourceManager->GetLevelProperties()->GetMapHeight())
            return;

        //modify the correct tiles tileID to the one of the selection
        Layer *currentModelLayer = resourceManager->GetLayer(currentLayer->GetLayerID());

        if(currentModelLayer)
        {
            currentModelLayer->ModifyTile(tileX, tileY, currentTile->GetTile()->GetID());
        }

        //repopulate the layer unless the function user says otherwise
        if(repopulate)
            RepopulateLayer(currentLayer);
    }
}

void LayerManager::FloodFill(int tileX, int tileY, int newTileID, int oldTileID)
{
    //this is a recursive function. It calls itself in tiles to the north, east, south and west.
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
        Layer *currentModelLayer = resourceManager->GetLayer(currentLayer->GetLayerID());

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
    }
}

void LayerManager::EraseTile(QPoint pos)
{
    if(!resourceManager || !currentTile || !currentLayer)
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
    }
}

void LayerManager::EyedropTile(QPoint pos)
{
    if(!resourceManager || !currentLayer)
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
    }
}

void LayerManager::AddLayer(QString name)
{
    Layer *tempLayer = new Layer;
    tempLayer->SetName(name);
    resourceManager->AddLayer(tempLayer);

    LayerGroup *tempLayerGroup = new LayerGroup;
    tempLayerGroup->SetLayerID(tempLayer->GetID());

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
    //pencil
    if(selectedTool == 0)
        ModifyTile(event->scenePos().toPoint());

    //eyedropper
    if(selectedTool == 1)
    {
        EyedropTile(event->scenePos().toPoint());
    }

    //bucket
    if(selectedTool == 3)
    {
        //translate the position to tile coordinates
        int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
        int tileH = resourceManager->GetLevelProperties()->GetTileHeight();

        int tileX = event->scenePos().toPoint().x() / tileW;
        int tileY = event->scenePos().toPoint().y() / tileH;

        Layer *tempLayer = resourceManager->GetLayer(currentLayer->GetLayerID());
        int oldTileID = tempLayer->GetTileType(tileX, tileY);

        FloodFill(tileX, tileY, currentTile->GetTile()->GetID(), oldTileID);

        RepopulateLayer(currentLayer);
    }

    //eraser
    if(selectedTool == 4)
    {
        EraseTile(event->scenePos().toPoint());
    }
}

void LayerManager::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //pencil
    if(selectedTool == 0)
        ModifyTile(event->scenePos().toPoint());

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

void LayerManager::RepopulateLayer(LayerGroup *dirtyLayer)
{
    if(!dirtyLayer)
        return;

    dirtyLayer->DeleteAllTileInstanceItems();

    TileInstanceItem *tempTileItem;

    Layer *dirtyModelLayer = resourceManager->GetLayer(currentLayer->GetLayerID());
    int tileCount = 0;

    if(dirtyModelLayer)
        tileCount = dirtyModelLayer->GetTileCount();

    int tileW = resourceManager->GetLevelProperties()->GetTileWidth();
    int tileH = resourceManager->GetLevelProperties()->GetTileHeight();
    int tileX = 0;
    int tileY = 0;

    for(int i = 0; i < tileCount; i++)
    {
        //create a new TileInstanceItem
        tempTileItem = new TileInstanceItem;
        TileInstance *tempTile = dirtyModelLayer->GetTileAtIndex(i);
        tempTileItem->SetTileInstance(tempTile);

        Tile *tempSelectionTile = resourceManager->GetTile(tempTile->GetTileID());

        //set the tile items pixmap
        QImage tempImage = *resourceManager->GetTileset();
        tempImage = tempImage.copy(tempSelectionTile->GetXOrigin() * tileW,
                                   tempSelectionTile->GetYOrigin() * tileH, tileW, tileH);

        tempTileItem->SetTilePixmap(QPixmap::fromImage(tempImage));

        tileX = dirtyModelLayer->GetTileAtIndex(i)->GetX();
        tileY = dirtyModelLayer->GetTileAtIndex(i)->GetY();

        //add it to the scene
        dirtyLayer->AddTileInstanceItem(tempTileItem);

        //set its position
        tempTileItem->setPos(tileX * tileW, tileY * tileH);
    }
}
