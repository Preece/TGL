#include "TileScene.h"

TileScene::TileScene()
{
    tileController = NULL;
    currentLayer = NULL;
    brushManager = NULL;

    grid = new QGraphicsItemGroup;
    addItem(grid);
    grid->setPos(0, 0);
    grid->hide();

    setItemIndexMethod(NoIndex);
}

TileScene::~TileScene()
{
}

void TileScene::RegisterTileController(TileController *newRC)
{
    tileController = newRC;

    connect(tileController, SIGNAL(TileUpdated(int,int,int,TileCoord)), this, SLOT(UpdateTile(int,int,int,TileCoord)));
    connect(tileController, SIGNAL(PreviewTileUpdated(int,int,TileCoord)), this, SLOT(UpdatePreviewTile(int,int,TileCoord)));
    connect(tileController, SIGNAL(SelectPreviewItems()), this, SLOT(SelectPreviewItems()));
    connect(tileController, SIGNAL(SelectionGeometryUpdated(QRect)), this, SLOT(UpdateSelectionGeometry(QRect)));
    connect(tileController, SIGNAL(ClearEraserPreview()), this, SLOT(ClearEraserPreview()));
    connect(tileController, SIGNAL(DrawEraserPreview(int,int)), this, SLOT(DrawEraserPreview(int,int)));
    connect(tileController, SIGNAL(LayerSizeUpdated(int,int)), this, SLOT(UpdateSceneSize(int,int)));
    connect(tileController, SIGNAL(LayerVisibilityUpdated(int,bool)), this, SLOT(UpdateLayerVisibility(int,bool)));
}

void TileScene::EyedropTile(QPoint pos)
{
    if(!tileController || !currentLayer)
        return;

    //translate the position to tile coordinates
    int tileW = tileController->GetTileWidth();
    int tileH = tileController->GetTileHeight();

    int tileX = pos.x() / tileW;
    int tileY = pos.y() / tileH;

    //if the position is beyond the bounds of the scene, ignore it
    //EVENTUALLY THE PARALLAX WILL NEED TO BE CONSIDERED
    if(tileX >= tileController->GetCurrentLayerWidth() || tileY >= tileController->GetCurrentLayerHeight())
        return;

    emit SelectNewTile(tileController->GetTileOrigin(tileX, tileY));

    RefreshPreview();
}

void TileScene::AddLayer(int newLayerID)
{
    //create a layer group, and assign the new layer
    TileLayerItem *tempLayerView = new TileLayerItem;
    tempLayerView->SetLayerID(newLayerID);
    tempLayerView->RegisterTileController(tileController);

    //put the layer group into the list
    layers.insert(0, tempLayerView);
    addItem(tempLayerView);
    UpdateLayerOpacity(newLayerID);

    tempLayerView->show();
    tempLayerView->setPos(0,0);
}

void TileScene::DeleteLayer(int ID)
{
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayerID() == ID)
        {
            layers[i]->DestroyAllItems();
            delete layers[i];
            layers.removeAt(i);
        }
    }
}

void TileScene::UpdateSceneSize(int w, int h)
{
    int newW, newH;

    if(w * tileController->GetTileWidth() > sceneRect().width())
        newW = w * tileController->GetTileWidth();

    if(h * tileController->GetTileHeight() > sceneRect().height())
        newH = h * tileController->GetTileHeight();
}

void TileScene::ToggleGrid(bool show)
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

    int tileW = tileController->GetTileWidth();
    int tileH = tileController->GetTileHeight();
    int mapH = tileController->GetCurrentLayerHeight();
    int mapW = tileController->GetCurrentLayerWidth();

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

void TileScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(!currentLayer)
        return;

    //translate the position to tile coordinates
    int tileW = tileController->GetTileWidth();
    int tileH = tileController->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    if(event->button() == Qt::LeftButton)
    {
        brushManager->GetCurrentBrush()->Press(tileX, tileY, tileController);
    }
    else if(event->button() == Qt::RightButton)
    {
        EyedropTile(event->scenePos().toPoint());

        //refresh the preview
        brushManager->GetCurrentBrush()->Paint(tileX, tileY, tileController, true);
    }
}

void TileScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(!currentLayer)
        return;

    //translate the position to tile coordinates
    int tileW = tileController->GetTileWidth();
    int tileH = tileController->GetTileHeight();

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
        brushManager->GetCurrentBrush()->Move(tileX, tileY, tileController, true);
    }
    //if the left mouse button was not down
    else if(currentLayer)
    {
        brushManager->GetCurrentBrush()->Move(tileX, tileY, tileController, false);
    }
}

void TileScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(!currentLayer)
        return;

    //translate the position to tile coordinates
    int tileW = tileController->GetTileWidth();
    int tileH = tileController->GetTileHeight();

    int tileX = event->scenePos().toPoint().x() / tileW;
    int tileY = event->scenePos().toPoint().y() / tileH;

    if(event->button() == Qt::LeftButton)
    {    
        brushManager->GetCurrentBrush()->Release(tileX, tileY, tileController);

        //this will package the changes into an undo command and implement them into the model
        //make it abort if the queue is empty
        tileController->EndPaintOperation();
    }
}

void TileScene::SetLayerSelection(int newSelection)
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

void TileScene::UpdateLayerVisibility(int ID, bool visible)
{
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayerID() == ID)
            layers[i]->setVisible(visible);
    }
}

void TileScene::RefreshPreview()
{
    ClearPreview();
    brushManager->GetCurrentBrush()->Paint(lastPreviewSpot.x(), lastPreviewSpot.y(), tileController, true);
}

void TileScene::ClearPreview()
{
    if(brushManager->GetCurrentBrush()->GetType() != "selector")
        tileController->ClearPreview();

    ClearEraserPreview();
}

void TileScene::SelectPreviewItems()
{
    QList<TileWidgetItem*> tileList = previewItems.values();

    for(int i = 0; i < tileList.count(); i++)
    {
        if(tileList[i])
            tileList[i]->setSelected(true);
    }
}

void TileScene::UpdateLayerOpacity(int opaqueLayerID)
{
    for(int i = 0; i < layers.count(); i++)
    {
        if(layers[i]->GetLayerID() == opaqueLayerID)
        {
            qreal opacity = tileController->GetLayerOpacity(opaqueLayerID);
            opacity = opacity / 100;
            layers[i]->setOpacity(opacity);
        }
    }
}

void TileScene::ToggleSelectionMode(bool selection)
{
    QList<QGraphicsItem*> childrenList = items();

    //make every current item selectable
    if(selection)
    {
        for(int i = 0; i < childrenList.count(); i++)
            childrenList[i]->setFlag(QGraphicsItem::ItemIsSelectable);

        tileController->EndPaintOperation();
    }
    //make all items non-selectable
    else
    {
        for(int i = 0; i < childrenList.count(); i++)
            childrenList[i]->setFlag(QGraphicsItem::ItemIsSelectable, false);

        ClearPreview();
    }
}

void TileScene::UpdateTile(int layerID, int x, int y, TileCoord newOrigin)
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

void TileScene::UpdatePreviewTile(int x, int y, TileCoord origin)
{
    if(origin == TileCoord(-1, -1))
    {
        if(previewItems.contains(TileCoord(x, y)))
        {
            removeItem(previewItems[TileCoord(x, y)]);
            delete previewItems[TileCoord(x, y)];
            previewItems.remove(TileCoord(x, y));
        }

        return;
    }

    TileWidgetItem *tempTile = new TileWidgetItem;
    tempTile->setFlag(QGraphicsItem::ItemIsSelectable);

    //update its Pixmap
    tempTile->SetTilePixmap(tileController->GetTilePixmap(origin));

    //set the position
    tempTile->setPos(x * tileController->GetTileWidth(),
                     y * tileController->GetTileHeight());

    previewItems[TileCoord(x, y)] = tempTile;
    addItem(tempTile);
}

void TileScene::UpdateSelectionGeometry(QRect rect)
{
    if(currentLayer)
        currentLayer->SelectTilesInArea(rect);
}

void TileScene::DrawEraserPreview(int x, int y)
{
    QGraphicsRectItem *rect = new QGraphicsRectItem(x * tileController->GetTileWidth(),
                           y * tileController->GetTileHeight(),
                           tileController->GetTileWidth(),
                           tileController->GetTileHeight());

    rect->setBrush(QBrush(QColor(0, 0, 255, 0x80)));
    rect->setPen(QPen(Qt::transparent));

    addItem(rect);
    eraserPreviewItems.append(rect);
}

void TileScene::ClearEraserPreview()
{
    for(int i = 0; i < eraserPreviewItems.count(); i++)
    {
        removeItem(eraserPreviewItems[i]);
        delete eraserPreviewItems[i];
        eraserPreviewItems[i] = NULL;
    }

    eraserPreviewItems.clear();
}
