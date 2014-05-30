#include "JSONExporter.h"

JSONExporter::JSONExporter()
{
}

void JSONExporter::Export(ResourceController *resources, QString filename)
{
    //get the data
    QList<Image*> images = resources->GetAllImages();
    QList<TileLayer*> layers = resources->GetAllLayers();
    LevelProperties *levelProps = resources->GetLevelProperties();

    //set up the JSON document
    QJsonObject documentObject;
    QJsonArray imageArray;
    QJsonArray layerArray;
    QJsonObject levelPropsObject;

    levelPropsObject["properties"] = ResourcePropertiesToJSON(levelProps);

    Image *currentImage;
    foreach(currentImage, images)
    {
        QJsonObject imageObject;
        imageObject["properties"] = ResourcePropertiesToJSON(currentImage);

        imageArray.append(imageObject);
    }

    TileLayer *currentLayer;
    foreach(currentLayer, layers)
    {
        QJsonObject layerObject;
        layerObject["properties"] = ResourcePropertiesToJSON(currentLayer);

        QHash<TileCoord, Tile> tiles = currentLayer->GetAllTiles();
        QHash<TileCoord, Tile>::iterator i = tiles.begin();

        QJsonArray tileArray;

        while(i != tiles.end())
        {
            QJsonObject tileObject;
            tileObject["oX"] = i.value().origin.first;
            tileObject["oY"] = i.value().origin.second;
            tileObject["x"] = i.value().pos.first;
            tileObject["y"] = i.value().pos.second;

            tileArray.append(tileObject);

            ++i;
        }

        layerObject["tiles"] = tileArray;

        layerArray.append(layerObject);
    }

    //fill out the document object
    documentObject["levelProperties"] = levelPropsObject;
    documentObject["images"] = imageArray;
    documentObject["layers"] = layerArray;

    QJsonDocument document(documentObject);

    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    file.write(document.toJson());
    file.close();
}

void JSONExporter::Import(ResourceController *resources, QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    QJsonDocument document = QJsonDocument::fromJson(file.readAll());

    file.close();

    QJsonObject documentObject = document.object();

    //load the level properties
    QJsonObject levelPropsObject = documentObject["levelProperties"].toObject();
    levelPropsObject = levelPropsObject["properties"].toObject();

    resources->GetLevelProperties()->SetLevelName(levelPropsObject["Name"].toString());

    //load the images
    QJsonArray imageArray = documentObject["images"].toArray();

    for(int i = 0; i < imageArray.count(); i++)
    {
        QJsonObject imageObject = imageArray[i].toObject();
        QJsonObject imageProperties = imageObject["properties"].toObject();

        Image *newImage = new Image;
        newImage->Load(imageProperties["id"].toInt(), ImageType, imageProperties.toVariantMap());

        resources->AddImage(newImage);
    }

    //load the layers
    QJsonArray layerArray = documentObject["layers"].toArray();

    for(int i = 0; i < layerArray.count(); i++)
    {
        QJsonObject layerObject = layerArray[i].toObject();
        QJsonObject layerProperties = layerObject["properties"].toObject();

        TileLayer *newLayer = resources->AddTileLayer();

        newLayer->Load(layerProperties["id"].toInt(), TileLayerType, layerProperties.toVariantMap());
    }
}

QJsonObject JSONExporter::ResourcePropertiesToJSON(ResourceNode *resource)
{
    QJsonObject propertiesObject;

    if(resource)
    {
        propertiesObject = QJsonObject::fromVariantMap(resource->GetAllProperties());
        propertiesObject["id"] = resource->GetID();
        propertiesObject["type"] = resource->GetType();
    }

    return propertiesObject;
}

