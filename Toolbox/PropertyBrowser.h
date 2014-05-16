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

    void RegisterResourceController(ResourceController *newRM) { resources = newRM; }

signals:
    void ResourceNameChanged(int resourceID, QString name);
    
public slots:

    void DisplayResource(ResourceNode *newResource);
    void UpdateValue(QtProperty *property, const QVariant &val);

private:
    ResourceNode *currentResource;

    ResourceController *resources;
    QtVariantPropertyManager *propertyManager;
    QtVariantEditorFactory *widgetFactory;
};

#endif // PROPERTYBROWSER_H
