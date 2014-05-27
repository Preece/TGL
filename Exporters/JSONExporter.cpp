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

    levelPropsObject["properties"] = QJsonObject::fromVariantMap(levelProps->GetAllProperties());

    Image *currentImage;
    foreach(currentImage, images)
    {
        QJsonObject propertiesObject = QJsonObject::fromVariantMap(currentImage->GetAllProperties());

        QJsonObject imageObject;
        imageObject["properties"] = propertiesObject;

        imageArray.append(imageObject);
    }

    TileLayer *currentLayer;
    foreach(currentLayer, layers)
    {
        QJsonObject propertiesObject = QJsonObject::fromVariantMap(currentLayer->GetAllProperties());

        QJsonObject layerObject;
        layerObject["properties"] = propertiesObject;

        layerArray.append(layerObject);
    }

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

}

void JSONExporter::WriteProperties(ResourceNode *resource, QJsonObject *object)
{
    //get a list of all the generic properties in the resource

    //loop through them, create their object, and add it to the object parameter

}
