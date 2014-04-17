#include "../Model/ResourceManager.h"

ResourceManager::ResourceManager()
{
    undo = new QUndoStack;
    undo->setUndoLimit(500);

    modifyTiles = new ModifyTilesCommand;
}

ResourceManager::~ResourceManager()
{
    if(modifyTiles)
        delete modifyTiles;
}

int ResourceManager::AddImage(Image *newImage)
{
    if(newImage)
    {
        AddResourceCommand *add = new AddResourceCommand(newImage, &imageMap);
        undo->push(add);

        emit ImageListModified();
    }

    return 0;
}

bool ResourceManager::DeleteImage(int ID)
{
    if(imageMap.value(ID))
    {
        DeleteResourceCommand *del = new DeleteResourceCommand(imageMap[ID], &imageMap);
        undo->push(del);

        emit ImageListModified();

        return true;
    }

    return false;
}

Image *ResourceManager::GetImageByIndex(int index)
{
    QList<Image*> images = imageMap.values();

    if(index >= images.count() || index < 0)
        return NULL;

    return images[index];
}

QImage *ResourceManager::GetTileset()
{
    if(levelProperties.GetTilesetID() == 0)
        return NULL;

    return GetImage(levelProperties.GetTilesetID())->GetImage();
}

QPixmap ResourceManager::GetTilePixmap(TileCoord coord)
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

void ResourceManager::AddTileLayer(TileLayer *newLayer)
{
    if(newLayer)
    {
        layerMap[newLayer->GetID()] = newLayer;

        emit LayerListModified(newLayer->GetID());
    }
}

void ResourceManager::DeleteTileLayer(int ID)
{
    if(layerMap.value(ID))
    {
        delete layerMap[ID];
        layerMap[ID] = NULL;
        layerMap.remove(ID);

        emit LayerListModified(ID);

        return;
    }
}

TileLayer *ResourceManager::GetTileLayer(int ID)
{
    if(layerMap.value(ID))
        return layerMap[ID];

    return NULL;
}

TileLayer *ResourceManager::GetLayerByIndex(int index)
{
    QList<TileLayer*> layers = layerMap.values();

    if(index < 0 || index > layers.count())
        return NULL;

    return layers[index];
}

int ResourceManager::GetLayerOpacity(int layerID)
{
    TileLayer *tempLayer = GetTileLayer(layerID);

    if(tempLayer)
        return tempLayer->GetOpacity();

    return 100;
}

void ResourceManager::ModifyTile(int layerID, int x, int y, TileCoord origin)
{
    TileLayer *tempLayer = layerMap.value(layerID);

    if(tempLayer)
    {
        modifyTiles->AddModification(GetTileLayer(layerID), x, y, origin, tempLayer->GetTileOrigin(x, y));
    }
}

TileCoord ResourceManager::GetTileOrigin(int layerID, int x, int y)
{
    //see if there is an upcoming modification to this tile
    TileCoord modOrigin = modifyTiles->GetTileOrigin(layerID, x, y);
    if(modOrigin != TileCoord(-1, -1))
        return modOrigin;

    //otherwise, check if the tile exists in the normal model
    if(layerMap.value(layerID))
    {
        TileLayer *tempLayer = layerMap.value(layerID);

        if(tempLayer)
            return tempLayer->GetTileOrigin(x, y);
    }

    return TileCoord(-1, -1);
}

int ResourceManager::GetTileCount(int layerID)
{
    if(layerMap.value(layerID))
    {
        return layerMap[layerID]->GetTileCount();
    }

    return 0;
}

Tile *ResourceManager::GetTileByIndex(int layerID, int i)
{
    if(layerMap.value(layerID))
    {
        return layerMap[layerID]->GetTileByIndex(layerID, i);
    }

    return NULL;
}

Image *ResourceManager::GetImage(int ID)
{
    if(imageMap.value(ID))
        return imageMap[ID];

    return NULL;
}

void ResourceManager::DestroyAllResources()
{
    delete undo;

    //destroy the images
    for(int i = 0; i < imageMap.count(); i++)
    {
        Image *image = GetImageByIndex(i);
        delete image;
        image = NULL;
    }

    imageMap.clear();

    for(int i = 0; i < layerMap.count(); i++)
    {
        TileLayer *layer = GetLayerByIndex(i);
        delete layer;
        layer = NULL;
    }

    layerMap.clear();
}

void ResourceManager::Undo()
{
    undo->undo();
}

void ResourceManager::Redo()
{
    undo->redo();
}

void ResourceManager::EndPaintOperation() 
{ 
    //if there are no changes that occured, no undo operation needs to be processed
    if(modifyTiles->GetModificationCount() == 0)
        return;

    //push the current bundle of modifications into the undo stack
    undo->push(modifyTiles); 

    //create a fresh bundle for the next operation
    modifyTiles = new ModifyTilesCommand;
}


