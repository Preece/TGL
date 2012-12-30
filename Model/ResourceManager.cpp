#include "../Model/ResourceManager.h"

ResourceManager::ResourceManager()
{
    undo = new QUndoStack;
    undo->setUndoLimit(100);
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
        objectPrototypeList.append(newObjectPrototype);
        return newObjectPrototype->GetID();
    }

    return 0;
}

bool ResourceManager::DeleteObjectPrototype(int ID)
{
    for(int i = 0; i < objectPrototypeList.count(); i++)
    {
        if(objectPrototypeList[i]->GetID() == ID)
        {
            delete objectPrototypeList[i];
            objectPrototypeList.removeAt(i);

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
    imageList.append(newImage);

    return newImage->GetID();
}

bool ResourceManager::DeleteImage(int ID)
{
    for(int i = 0; i < imageList.count(); i++)
    {
        if(imageList[i]->GetID() == ID)
        {
            delete imageList[i];
            imageList.removeAt(i);
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
        tileList.append(newTile);
}

void ResourceManager::ClearTiles()
{
    for(int i = 0; i < GetTileCount(); i++)
    {
        if(tileList[i])
            delete tileList[i];
    }

    tileList.clear();
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

void ResourceManager::AddLayer(Layer *newLayer)
{
    if(newLayer)
        layerList.insert(0, newLayer);
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
    }

    //clear the list
    spriteList.clear();

    //destroy the images
    for(int i = 0; i < imageList.count(); i++)
    {
        delete imageList[i];
    }

    imageList.clear();
}

void ResourceManager::Undo()
{
    undo->undo();
}

void ResourceManager::Redo()
{
    undo->redo();
}


