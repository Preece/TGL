#ifndef RESOURCEVIEW_H
#define RESOURCEVIEW_H

#include <QTreeWidget>
#include <QString>

#include "Model/ResourceManager.h"

class ResourceView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ResourceView(QWidget *parent = 0);

    void RegisterResourceManager(ResourceManager *rm) { resources = rm; }

    void RepopulateEverything();

    int GetSelectedID();

    bool IsLayerSelected();
    
signals:
    void NewResourceSelected(ObjectNode *newObject);
    
public slots:
    void selectionUpdated(QTreeWidgetItem*, int);

private:
    ResourceManager *resources;

    QTreeWidgetItem *projectRoot;
    QTreeWidgetItem *layerRoot;
    QTreeWidgetItem *imageRoot;
    QTreeWidgetItem *tilesetRoot;

    ObjectNode *currentSelection;

    int GetItemID(QTreeWidgetItem *item);
    QTreeWidgetItem *AddNode(QTreeWidgetItem *parent, QString name, QString icon, int ID = 0);
    void RemoveChildrenNodes(QTreeWidgetItem *parent);
    
};

#endif // RESOURCEVIEW_H
