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
}

void LayerManager::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //pencil
    if(selectedTool == 0)
        ModifyTile(event->scenePos().toPoint());
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
        tempTileItem->SetTileInstance(dirtyModelLayer->GetTileAtIndex(i));

        //set the tile items pixmap
        tempTileItem->SetTilePixmap(currentTile->GetTilePixmap());

        tileX = dirtyModelLayer->GetTileAtIndex(i)->GetX();
        tileY = dirtyModelLayer->GetTileAtIndex(i)->GetY();

        //add it to the scene
        dirtyLayer->AddTileInstanceItem(tempTileItem);

        //set its position
        tempTileItem->setPos(tileX * tileW, tileY * tileH);
    }
}
