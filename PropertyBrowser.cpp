#include "PropertyBrowser.h"

PropertyBrowser::PropertyBrowser(QWidget *parent) :
    QtTreePropertyBrowser(parent)
{
    resources = NULL;

    propertyManager = new QtVariantPropertyManager;
    widgetFactory = new QtVariantEditorFactory;


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

    //if its an image

    //if its a tileset
}

void PropertyBrowser::DisplayLevelProperties(LevelProperties *properties)
{
    QtVariantProperty *levelName = propertyManager->addProperty(QVariant::String, "Level Name");
    levelName->setAttribute("value", properties->GetLevelName());

    setFactoryForManager(propertyManager, widgetFactory);
}

void PropertyBrowser::DisplayLayer(TileLayer *layer)
{
}
