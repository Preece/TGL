#include "PropertyBrowser.h"

PropertyBrowser::PropertyBrowser(QWidget *parent) :
    QtTreePropertyBrowser(parent)
{
    resources = NULL;
    currentObject = NULL;

    propertyManager = new QtVariantPropertyManager;
    widgetFactory = new QtVariantEditorFactory;
    setFactoryForManager(propertyManager, widgetFactory);

    connect(propertyManager, SIGNAL(valueChanged(QtProperty*,QVariant)), this, SLOT(UpdateValue(QtProperty*,QVariant)));
}

PropertyBrowser::~PropertyBrowser()
{
    delete propertyManager;
    delete widgetFactory;
}

void PropertyBrowser::DisplayResource(ObjectNode *newObject)
{
    //clear out all the values
    clear();

    if(!resources)
        return;

    currentObject = newObject;

    DisplayObject(newObject);
}

void PropertyBrowser::UpdateValue(QtProperty *property, const QVariant &val)
{
    if(currentObject)
    {
        currentObject->SetProperty(property->propertyName(), val);
    }
}

void PropertyBrowser::DisplayObject(ObjectNode *object)
{
    PropertyList properties = object->GetAllProperties();

    PropertyList::iterator i;
    for(i = properties.begin(); i != properties.end(); ++i)
    {
        QtVariantProperty *newProperty = propertyManager->addProperty(i.value().type(), i.key());
        newProperty->setValue(i.value());
        addProperty(newProperty);
    }
}
