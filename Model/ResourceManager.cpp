#include "../Model/ResourceManager.h"

ResourceManager::ResourceManager()
{
    undo = new QUndoStack;
    undo->setUndoLimit(500);
    
    undoing = false;
}

int ResourceManager::AddSprite(Sprite *newSprite)
{
    if(newSprite != NULL)
    {
        //create an add sprite command
        AddResourceCommand *add = new AddResourceCommand(newSprite, &spriteMap);

        //push it into the undo list
        undo->push(add);
    }

    return 0;
}

bool ResourceManager::DeleteSprite(int ID)
{
    if(spriteMap.value(ID))
    {
        DeleteResourceCommand *del = new DeleteResourceCommand(spriteMap[ID], &spriteMap);
        undo->push(del);

        return true;
    }

    return false;
}

Sprite *ResourceManager::GetSprite(int ID)
{
    if(spriteMap.value(ID))
        return spriteMap[ID];

    return NULL;
}

Sprite *ResourceManager::GetSpriteByIndex(int index)
{
    QList<Sprite*> sprites = spriteMap.values();

    if(index >= sprites.count() || index < 0)
        return NULL;

    return sprites[index];
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

QPixmap ResourceManager::GetSpriteSymbol(int spriteID)
{
    //get the sprite based on its ID
    Sprite *tempSprite = GetSprite(spriteID);

    //if its a valid sprite
    if(tempSprite)
    {
        Image *tempImage = GetImage(tempSprite->GetImageID());

        //if the image is valid
        if(tempImage)
        {
            //get the image
            QImage *tempQImage = tempImage->GetImage();

            //if the image is valid
            if(tempQImage)
            {
                //if the sprite has an animation and frame
                if(tempSprite->GetAnimationCount() > 0)
                    if(tempSprite->GetAnimationByIndex(0)->GetFrameCount() > 0)
                    {
                        //get the frame rect and make a pixmap from it
                        QRect frameRect = tempSprite->GetAnimationByIndex(0)->GetFrameAtIndex(0)->GetFrameRect();
                        QPixmap tempPixmap = QPixmap::fromImage(tempQImage->copy(frameRect));
                        return tempPixmap;
                    }
            }

        }
    }

    //return the missing file symbol
    return QPixmap(":/Icons/Icons/MissingFile.png");
}

QImage *ResourceManager::GetTileset()
{
    if(levelProperties.GetTilesetID() == 0)
        return NULL;

    return GetImage(levelProperties.GetTilesetID())->GetImage();
}

QPixmap ResourceManager::GetTilePixmap(TileCoord coord)
{
    //commented out for refactoring

    QImage *tempTileset = GetTileset();
    QImage tempImage = *tempTileset;

    if(tempImage.isNull())
        return QPixmap();

    tempImage = tempImage.copy(levelProperties.GetTileWidth() * coord.first, levelProperties.GetTileHeight() * coord.second, levelProperties.GetTileWidth(), levelProperties.GetTileHeight());

    return QPixmap::fromImage(tempImage);
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
}

void ResourceManager::ModifyTile(int layerID, int x, int y, TileCoord origin)
{
    //use a modify tile command
    if(layerMap.value(layerID))
    {
        layerMap[layerID]->ModifyTile(x, y, origin);
    }
}

TileCoord ResourceManager::GetTileOrigin(int layerID, int x, int y)
{
    if(layerMap.value(layerID))
    {
        TileLayer *tempLayer = layerMap.value(layerID);

        if(tempLayer)
        {
            return tempLayer->GetTileOrigin(x, y);
        }
    }

    return TileCoord(-1, -1);
}

void ResourceManager::AddTileToLayer(int layerID, int x, int y, TileCoord origin)
{
    //use the command
    if(layerMap.value(layerID))
    {
        TileLayer *tempLayer = layerMap.value(layerID);

        if(tempLayer)
        {
            tempLayer->AddTile(TileCoord(x, y), origin);
        }
    }
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

    //destroy the sprite resources
    for(int i = 0; i < spriteMap.count(); i++)
    {
        Sprite *sprite = GetSpriteByIndex(i);
        sprite->DestroyAllAnimations();
        delete sprite;
        sprite = NULL;
    }

    //clear the list
    spriteMap.clear();

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

void ResourceManager::BeginUndoOperation(QString name) 
{ 
    undoing = true;
    undo->beginMacro(name); 
}

void ResourceManager::EndUndoOperation() 
{ 
    undoing = false;
    undo->endMacro(); 
}


