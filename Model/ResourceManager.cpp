#include "../Model/ResourceManager.h"

ResourceManager::ResourceManager()
{
    undo = new QUndoStack;
    undo->setUndoLimit(500);
}

int ResourceManager::AddSprite(Sprite *newSprite)
{
    if(newSprite != NULL)
    {
        //create an add sprite command
        AddResourceCommand *add = new AddResourceCommand(newSprite, &spriteList);

        //push it into the undo list
        undo->push(add);
    }

    return 0;
}

bool ResourceManager::DeleteSprite(int ID)
{
    for(int i = 0; i < spriteList.count(); i++)
    {
        if(spriteList[i]->GetID() == ID)
        {
            DeleteResourceCommand *del = new DeleteResourceCommand(spriteList[i], &spriteList);
            undo->push(del);

            return true;
        }
    }
    return false;
}

Sprite *ResourceManager::GetSprite(int ID)
{
    for(int i = 0; i < spriteList.count(); i++)
    {
        if(spriteList[i]->GetID() == ID)
            return spriteList[i];
    }

    return NULL;
}

Sprite *ResourceManager::GetSpriteByIndex(int index)
{
    if(index >= spriteList.count() || index < 0)
        return NULL;

    return spriteList[index];
}

int ResourceManager::AddObjectPrototype(ObjectPrototype *newObjectPrototype)
{
    if(newObjectPrototype != NULL)
    {
        AddResourceCommand *add = new AddResourceCommand(newObjectPrototype, &objectPrototypeList);
        undo->push(add);
    }

    return 0;
}

bool ResourceManager::DeleteObjectPrototype(int ID)
{
    for(int i = 0; i < objectPrototypeList.count(); i++)
    {
        if(objectPrototypeList[i]->GetID() == ID)
        {
            DeleteResourceCommand *del = new DeleteResourceCommand(objectPrototypeList[i], &objectPrototypeList);
            undo->push(del);

            return true;
        }
    }
    return false;
}

ObjectPrototype *ResourceManager::GetObjectPrototype(int ID)
{
    return NULL;
}

ObjectPrototype *ResourceManager::GetObjectPrototypeByIndex(int index)
{
    if(index < 0 || index >= objectPrototypeList.count())
        return NULL;

    return objectPrototypeList[index];
}

int ResourceManager::AddObjectInstance(ObjectInstance *newObjectInstance)
{
    if(newObjectInstance)
        objectInstanceList.append(newObjectInstance);

    return 0;
}

bool ResourceManager::DeleteObjectInstance(int ID)
{
    return false;
}

ObjectInstance *ResourceManager::GetObjectInstance(int ID)
{
    return NULL;
}

int ResourceManager::AddImage(Image *newImage)
{
    if(newImage)
    {
        AddResourceCommand *add = new AddResourceCommand(newImage, &imageList);
        undo->push(add);
    }

    return 0;
}

bool ResourceManager::DeleteImage(int ID)
{
    for(int i = 0; i < imageList.count(); i++)
    {
        if(imageList[i]->GetID() == ID)
        {
            DeleteResourceCommand *del = new DeleteResourceCommand(imageList[i], &imageList);
            undo->push(del);
            return true;
        }
    }

    return false;
}

Image *ResourceManager::GetImageByIndex(int index)
{
    if(index >= imageList.count() || index < 0)
    {
        return NULL;
    }

    return imageList[index];
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

QPixmap ResourceManager::GetTilePixmap(int ID)
{
    QImage *tempTileset = GetTileset();
    QImage tempImage = *tempTileset;

    if(tempImage.isNull())
        return QPixmap();

    Tile *tempTile = GetTile(ID);

    if(tempTile == NULL)
        return QPixmap();

    tempImage = tempImage.copy(levelProperties.GetTileWidth() * tempTile->GetXOrigin(),
                                levelProperties.GetTileHeight() * tempTile->GetYOrigin(),
                                levelProperties.GetTileWidth(), levelProperties.GetTileHeight());

    return QPixmap::fromImage(tempImage);
}

void ResourceManager::AddTile(Tile *newTile)
{
    if(newTile)
    {
        AddResourceCommand *add = new AddResourceCommand(newTile, &tileList);
        undo->push(add);
    }
}

void ResourceManager::ClearTiles()
{
    undo->beginMacro("Clear Tiles");

    DeleteResourceCommand *del;

    for(int i = 0; i < GetTileCount(); i++)
    {
        //keep removing the first element
        del = new DeleteResourceCommand(tileList[0], &tileList);
        undo->push(del);
    }

    undo->endMacro();
}

Tile *ResourceManager::GetTile(int ID)
{
    for(int i = 0; i < GetTileCount(); i++)
    {
        if(tileList[i]->GetID() == ID)
            return tileList[i];
    }

    return NULL;
}

Tile *ResourceManager::GetTile(int x, int y)
{
    for(int i = 0; i < GetTileCount(); i++)
    {
        if(tileList[i]->GetXOrigin() == x && tileList[i]->GetYOrigin() == y)
            return tileList[i];
    }

    return NULL;
}

TileInstance *ResourceManager::AddTileInstance(Layer *layer, int x, int y, int newType)
{
    AddTilesCommand *add = new AddTilesCommand(layer, x, y, newType);
    undo->push(add);

    return add->GetTileInstance();
}

void ResourceManager::ModifyTileInstance(Layer *layer, int x, int y, int newType, int oldType)
{
    //if(newType == oldType)
      //  return;

    ModifyTilesCommand *mod = new ModifyTilesCommand(layer, x, y, newType, oldType);
    undo->push(mod);
}

TileInstance *ResourceManager::GetTileInstanceByIndex(Layer *layer, int i)
{
    if(i < 0 || i >= layer->GetTileCount())
        return NULL;

    if(!layer)
        return NULL;

    return layer->GetTileAtIndex(i);
}

int ResourceManager::GetTileInstanceCount(Layer *layer)
{
    if(!layer)
        return 0;

    return layer->GetTileCount();
}

void ResourceManager::AddLayer(Layer *newLayer)
{
    if(newLayer)
    {
        layerList.append(newLayer);
    }
}

void ResourceManager::DeleteLayer(int ID)
{
    for(int i = 0; i < layerList.count(); i++)
    {
        if(layerList[i]->GetID() == ID)
        {
            delete layerList[i];
            layerList.removeAt(i);

            return;
        }
    }
}

Layer *ResourceManager::GetLayer(int ID)
{
    for(int i = 0; i < layerList.count(); i++)
    {
        if(layerList[i]->GetID() == ID)
        {
            return layerList[i];
        }
    }

    return NULL;
}

Layer *ResourceManager::GetLayerByIndex(int index)
{
    if(index < 0 || index > layerList.count())
        return NULL;

    return layerList[index];
}

Image *ResourceManager::GetImage(int ID)
{
    for(int i = 0; i < imageList.count(); i++)
    {
        if(imageList[i]->GetID() == ID)
            return imageList[i];
    }

    return NULL;
}

void ResourceManager::DestroyAllResources()
{
    delete undo;

    //destroy the sprite resources
    for(int i = 0; i < spriteList.count(); i++)
    {
        spriteList[i]->DestroyAllAnimations();
        delete spriteList[i];
        spriteList[i] = NULL;
    }

    //clear the list
    spriteList.clear();

    //destroy the images
    for(int i = 0; i < imageList.count(); i++)
    {
        delete imageList[i];
        imageList[i] = NULL;
    }

    imageList.clear();

    for(int i = 0; i < objectPrototypeList.count(); i++)
    {
        delete objectPrototypeList[i];
        objectPrototypeList[i] = NULL;
    }

    objectPrototypeList.clear();

    for(int i = 0; i < tileList.count(); i++)
    {
        delete tileList[i];
        tileList[i] = NULL;
    }

    tileList.clear();

    for(int i = 0; i < objectInstanceList.count(); i++)
    {
        delete objectInstanceList[i];
        objectInstanceList[i] = NULL;
    }

    objectInstanceList.clear();

    for(int i = 0; i < layerList.count(); i++)
    {
        delete layerList[i];
        layerList[i] = NULL;
    }

    layerList.clear();
}

void ResourceManager::Undo()
{
    undo->undo();
}

void ResourceManager::Redo()
{
    undo->redo();
}


