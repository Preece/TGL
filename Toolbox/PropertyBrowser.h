#ifndef PROPERTYBROWSER_H
#define PROPERTYBROWSER_H

#include <QtTreePropertyBrowser>
#include <QtVariantPropertyManager>
#include <QtVariantEditorFactory>

#include "Model/ResourceController.h"

class PropertyBrowser : public QtTreePropertyBrowser
{
    Q_OBJECT
public:
    explicit PropertyBrowser(QWidget *parent = 0);
    ~PropertyBrowser();

    void RegisterResourceManager(ResourceController *newRM) { resources = newRM; }
    
signals:
    void ResourceNameChanged(int ID, QString name);
    
public slots:

    void DisplayResource(ResourceNode *newObject);
    void UpdateValue(QtProperty *property, const QVariant &val);

private:
    ResourceNode *currentObject;
    void DisplayObject(ResourceNode *object);

    ResourceController *resources;
    QtVariantPropertyManager *propertyManager;
    QtVariantEditorFactory *widgetFactory;
};

#endif // PROPERTYBROWSER_H
