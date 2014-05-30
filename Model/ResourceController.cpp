#include "../Model/ResourceController.h"

ResourceController::ResourceController()
{
    undo = new QUndoStack;
    undo->setUndoLimit(500);

    clipboard = new Clipboard;
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
        AddResourceCommand *add = new AddResourceCommand(newImage, &images);
        undo->push(add);

        emit ResourceAdded(newImage->GetID());
    }

    return 0;
}

bool ResourceController::DeleteImage(int ID)
{
    if(images.value(ID))
    {
        DeleteResourceCommand *del = new DeleteResourceCommand(images[ID], &images);
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

TileLayer *ResourceController::AddTileLayer()
{
    TileLayer *newLayer = new TileLayer;
    newLayer->SetType(TileLayerType);
    layers[newLayer->GetID()] = newLayer;

    emit ResourceAdded(newLayer->GetID());
    emit LayerAdded(newLayer->GetID());

    return newLayer;
}

void ResourceController::DeleteTileLayer(int ID)
{
    if(layers.contains(ID))
    {
        delete layers[ID];
        layers[ID] = NULL;
        layers.remove(ID);

        emit ResourceDeleted(ID);
        emit LayerRemoved(ID);
    }
}

TileLayer *ResourceController::GetTileLayer(int ID)
{
    if(layers.value(ID))
        return layers[ID];

    return NULL;
}

QList<TileLayer *> ResourceController::GetAllLayers()
{
    return layers.values();
}

Image *ResourceController::GetImage(int imageID)
{
    if(images.value(imageID))
        return images[imageID];

    return NULL;
}

QList<Image *> ResourceController::GetAllImages()
{
    return images.values();
}

void ResourceController::DestroyAllResources()
{
    undo->clear();

    //destroy the images
    QList<Image*> imageList = images.values();
    for(int i = 0; i < imageList.count(); i++)
    {
        emit ResourceDeleted(imageList[i]->GetID());

        delete imageList[i];
        imageList[i] = NULL;
    }
    images.clear();

    QList<TileLayer*> layerList = layers.values();
    for(int i = 0; i < layerList.count(); i++)
    {
        emit ResourceDeleted(layerList[i]->GetID());
        emit LayerRemoved(layerList[i]->GetID());

        delete layerList[i];
        layerList[i] = NULL;
    }
    layers.clear();
}

void ResourceController::Undo()
{
    undo->undo();
}

void ResourceController::Redo()
{
    undo->redo();
}

ResourceNode *ResourceController::GetResource(int ID)
{
    if(ID == levelProperties.GetID())
        return &levelProperties;

    QHash<int,Image*>::iterator imageIter;
    for(imageIter = images.begin(); imageIter != images.end(); ++imageIter)
    {
        if(imageIter.key() == ID)
            return imageIter.value();
    }

    QHash<int,TileLayer*>::iterator layerIter;
    for(layerIter = layers.begin(); layerIter != layers.end(); ++layerIter)
    {
        if(layerIter.key() == ID)
            return layerIter.value();
    }

    return NULL;
}
