#include "PropertyBrowser.h"

PropertyBrowser::PropertyBrowser(QWidget *parent) :
    QtTreePropertyBrowser(parent)
{
    resources = NULL;
    currentResource = NULL;

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

void PropertyBrowser::DisplayResource(ResourceNode *newResource)
{
    //clear out all the values
    clear();

    if(!resources)
        return;

    currentResource = newResource;

    PropertyList properties = newResource->GetAllProperties();

    //pull out the name property first, it should be on top
    if(properties.contains("Name"))
    {
        QtVariantProperty *newProperty = propertyManager->addProperty(properties["Name"].type(), "Name");
        newProperty->setValue(properties["Name"]);
        addProperty(newProperty);
    }

    PropertyList::iterator i;
    for(i = properties.begin(); i != properties.end(); ++i)
    {
        if(i.key() != "Name")
        {
            QtVariantProperty *newProperty = propertyManager->addProperty(i.value().type(), i.key());
            newProperty->setValue(i.value());
            addProperty(newProperty);
        }
    }
}

void PropertyBrowser::UpdateValue(QtProperty *property, const QVariant &val)
{
    if(currentResource)
    {
        currentResource->SetProperty(property->propertyName(), val);

        //update the name in the resource viewer
        if(property->propertyName() == "Name")
            emit ResourceNameChanged(currentResource->GetID(), val.toString());
    }
}
