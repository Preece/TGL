#include "PropertyBrowser.h"

PropertyBrowser::PropertyBrowser(QWidget *parent) :
    QtTreePropertyBrowser(parent)
{
    resources = NULL;

    propertyManager = new QtVariantPropertyManager;
    widgetFactory = new QtVariantEditorFactory;

    setFactoryForManager(propertyManager, widgetFactory);
}

PropertyBrowser::~PropertyBrowser()
{
    delete propertyManager;
    delete widgetFactory;
}

void PropertyBrowser::DisplayResource(int ID)
{
    //clear out all the values
    clear();

    if(!resources)
        return;

    //check sequentially against each type of resource to see what it is

    //if its the level properties
    if(resources->GetLevelProperties()->GetID() == ID)
        DisplayLevelProperties(resources->GetLevelProperties());

    //if its a layer
    if(resources->GetTileLayer(ID))
        DisplayLayer(resources->GetTileLayer(ID));

    //if its an image
    if(resources->GetImage(ID))
        DisplayImage(resources->GetImage(ID));

    //if its a tileset
}

void PropertyBrowser::DisplayLevelProperties(LevelProperties *properties)
{
    //valueChanged(QtProperty *property, const QVariant &val);
    //this is the signal emitted by the property manager when a value is modified.
    //another function should connect into this, determine what property is being 
    //modified, and actually change it in the resource manager

    //add the level name
    QtVariantProperty *newProperty = propertyManager->addProperty(QVariant::String, "Level Name");
    newProperty->setAttribute("value", properties->GetLevelName());
    addProperty(newProperty);

    //add the tile size
    newProperty = propertyManager->addProperty(QVariant::Point, "Tile Size");
    newProperty->setValue(QPoint(properties->GetTileWidth(), properties->GetTileHeight()));
    newProperty->setAttribute("expanded", false);
    addProperty(newProperty);

    //add the map size
    newProperty = propertyManager->addProperty(QVariant::Point, "Map Size (in tiles)");
    newProperty->setValue(QPoint(properties->GetMapWidth(), properties->GetMapHeight()));
    addProperty(newProperty);
}

void PropertyBrowser::DisplayLayer(TileLayer *layer)
{
    QtVariantProperty *newProperty = propertyManager->addProperty(QVariant::String, "Layer Name");
    newProperty->setValue(layer->GetName());
    addProperty(newProperty);

    //parallax
    newProperty = propertyManager->addProperty(QVariant::PointF, "Parallax Coefficients");
    newProperty->setValue(QPointF(layer->GetHorizontalParallax(), layer->GetVerticalParallax()));
    newProperty->setAttribute("decimals", 2);
    addProperty(newProperty);

    //opacity
    newProperty = propertyManager->addProperty(QVariant::Int, "Opacity");
    newProperty->setValue(layer->GetOpacity());
    newProperty->setAttribute("minimum", 0);
    newProperty->setAttribute("maximum", 100);
    newProperty->setAttribute("singleStep", 10);
    addProperty(newProperty);

}

void PropertyBrowser::DisplayImage(Image *img)
{
    //add the image name
    QtVariantProperty *newProperty = propertyManager->addProperty(QVariant::String, "Image Name");
    newProperty->setValue(QVariant(img->GetImageName()));
    addProperty(newProperty);

    //add the file path
    newProperty = propertyManager->addProperty(QVariant::String, "File Path");
    newProperty->setValue(QVariant(img->GetFilename()));
    addProperty(newProperty);
}