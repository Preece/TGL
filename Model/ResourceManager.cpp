#include "../Model/ResourceManager.h"

ResourceManager::ResourceManager()
{
}

int ResourceManager::AddSprite(Sprite *newSprite)
{
    if(newSprite != NULL)
    {
        spriteList.append(newSprite);
        return newSprite->GetID();
    }

    return NULL;
}

bool ResourceManager::DeleteSprite(int ID)
{
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

    return NULL;
}

bool ResourceManager::DeleteObjectPrototype(int ID)
{
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


