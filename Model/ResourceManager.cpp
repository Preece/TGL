#include "../Model/resourcemanager.h"

ResourceManager::ResourceManager()
{
}

int ResourceManager::AddSprite(Sprite *newSprite)
{
    return 0;
}

bool ResourceManager::DeleteSprite(int ID)
{
    return false;
}

Sprite *ResourceManager::GetSprite(int ID)
{
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
    return 0;
}

bool ResourceManager::DeleteObjectPrototype(int ID)
{
    return false;
}

ObjectPrototype *ResourceManager::GetObjectPrototype(int ID)
{
    return NULL;
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
        QMessageBox::warning(NULL, "Warning", "Tried to Get an Image by index. Failed.");
        return NULL;
    }

    return imageList[index];
}

Image *ResourceManager::GetImage(int ID)
{
    for(int i = 0; i < imageList.count(); i++)
    {
        if(imageList[i]->GetID() == ID)
            return imageList[i];
    }

    QMessageBox::warning(NULL, "Warning", "You attempted to access an Image by ID. It was not found.");
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


