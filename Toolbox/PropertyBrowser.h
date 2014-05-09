#ifndef PROPERTYBROWSER_H
#define PROPERTYBROWSER_H

#include <QtTreePropertyBrowser>
#include <QtVariantPropertyManager>
#include <QtVariantEditorFactory>

#include "Model/ResourceManager.h"

class PropertyBrowser : public QtTreePropertyBrowser
{
    Q_OBJECT
public:
    explicit PropertyBrowser(QWidget *parent = 0);
    ~PropertyBrowser();

    void RegisterResourceManager(ResourceManager *newRM) { resources = newRM; }
    
signals:
    
public slots:

    void DisplayResource(ObjectNode *newObject);
    void UpdateValue(QtProperty *property, const QVariant &val);

private:
    ObjectNode *currentObject;
    void DisplayObject(ObjectNode *object);

    ResourceManager *resources;
    QtVariantPropertyManager *propertyManager;
    QtVariantEditorFactory *widgetFactory;
};

#endif // PROPERTYBROWSER_H
