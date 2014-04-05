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

    void DisplayResource(int ID);

private:
    void DisplayLevelProperties(LevelProperties *properties);
    void DisplayLayer(TileLayer *layer);
    void DisplayImage(Image *img);

    ResourceManager *resources;
    QtVariantPropertyManager *propertyManager;
    QtVariantEditorFactory *widgetFactory;
    
};

#endif // PROPERTYBROWSER_H
