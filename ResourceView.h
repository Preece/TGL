#ifndef RESOURCEVIEW_H
#define RESOURCEVIEW_H

#include <QTreeWidget>

#include "Model/ResourceManager.h"

class ResourceView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ResourceView(QWidget *parent = 0);

    void RegisterResourceManager(ResourceManager *rm) { resources = rm; }

    void RepopulateEverything();
    
signals:
    
public slots:

private:
    ResourceManager *resources;
    
};

#endif // RESOURCEVIEW_H
