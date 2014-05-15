#include "../Model/ResourceController.h"

ResourceController::ResourceController()
{
    undo = new QUndoStack;
    undo->setUndoLimit(500);

    clipboard = new Clipboard;

    defaultLayer.SetName("Default");
    layerMap[defaultLayer.GetID()] = &defaultLayer;
    emit ResourceAdded(defaultLayer.GetID());
}

ResourceController::~ResourceController()
{
    delete clipboard;
}

int ResourceController::GetTileWidth()
{
    return levelProperties.GetTileWidth();
}

int ResourceController::GetTileHeight()
{
    return levelProperties.GetTileHeight();
}

int ResourceController::AddImage(Image *newImage)
{
    if(newImage)
    {
        newImage->SetType(ImageType);
        AddResourceCommand *add = new AddResourceCommand(newImage, &imageMap);
        undo->push(add);

        emit ResourceAdded(newImage->GetID());
    }

    return 0;
}

bool ResourceController::DeleteImage(int ID)
{
    if(imageMap.value(ID))
    {
        DeleteResourceCommand *del = new DeleteResourceCommand(imageMap[ID], &imageMap);
        undo->push(del);

        emit ResourceDeleted(ID);

        return true;
    }

    return false;
}

QImage *ResourceController::GetTileset()
{
    if(levelProperties.GetTilesetID() == 0)
        return NULL;

    return GetImage(levelProperties.GetTilesetID())->GetImage();
}

QPixmap ResourceController::GetTilePixmap(TileCoord coord)
{
    if(pixmapCache.contains(coord))
        return pixmapCache[coord];

    QImage *tempTileset = GetTileset();
    QImage tempImage = *tempTileset;

    if(tempImage.isNull())
        return QPixmap();

    tempImage = tempImage.copy(levelProperties.GetTileWidth() * coord.first, levelProperties.GetTileHeight() * coord.second, levelProperties.GetTileWidth(), levelProperties.GetTileHeight());

    pixmapCache[coord] = QPixmap::fromImage(tempImage);
    return pixmapCache[coord];
}

void ResourceController::AddTileLayer()
{
    TileLayer *newLayer = new TileLayer;
    newLayer->SetType(TileLayerType);
    layerMap[newLayer->GetID()] = newLayer;

    emit ResourceAdded(newLayer->GetID());
    emit LayerAdded(newLayer->GetID());
}

void ResourceController::DeleteTileLayer(int ID)
{
    if(layerMap.contains(ID))
    {
        delete layerMap[ID];
        layerMap[ID] = NULL;
        layerMap.remove(ID);

        emit ResourceDeleted(ID);
        emit LayerRemoved(ID);
    }
}

TileLayer *ResourceController::GetTileLayer(int ID)
{
    if(layerMap.value(ID))
        return layerMap[ID];

    return NULL;
}

Image *ResourceController::GetImage(int imageID)
{
    if(imageMap.value(imageID))
        return imageMap[imageID];

    return NULL;
}

void ResourceController::DestroyAllResources()
{
    delete undo;

    //destroy the images
    QList<Image*> imageList = imageMap.values();
    for(int i = 0; i < imageList.count(); i++)
    {
        delete imageList[i];
        imageList[i] = NULL;
    }
    imageMap.clear();

    QList<TileLayer*> layerList = layerMap.values();
    for(int i = 0; i < layerList.count(); i++)
    {
        if(layerList[i] != &defaultLayer)
        {
            delete layerList[i];
            layerList[i] = NULL;
        }
    }
    layerMap.clear();
}

void ResourceController::Undo()
{
    undo->undo();
}

void ResourceController::Redo()
{
    undo->redo();
}

ResourceNode *ResourceController::GetObject(int ID)
{
    if(ID == levelProperties.GetID())
        return &levelProperties;

    QHash<int,Image*>::iterator imageIter;
    for(imageIter = imageMap.begin(); imageIter != imageMap.end(); ++imageIter)
    {
        if(imageIter.key() == ID)
            return imageIter.value();
    }

    QHash<int,TileLayer*>::iterator layerIter;
    for(layerIter = layerMap.begin(); layerIter != layerMap.end(); ++layerIter)
    {
        if(layerIter.key() == ID)
            return layerIter.value();
    }

    return NULL;
}
