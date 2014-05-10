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

    void paintEvent(QPaintEvent* e) { QTreeWidget::paintEvent(e); }
    
signals:
    void NewResourceSelected(ObjectNode *newObject);
    
public slots:
    void selectionUpdated(QTreeWidgetItem*, int);

    void AddResource(int ID);
    void RemoveResource(int ID);

    void UpdateResourceName(int ID, QString name);

private:
    ResourceManager *resources;

    QTreeWidgetItem *projectRoot;
    QTreeWidgetItem *layerRoot;
    QTreeWidgetItem *imageRoot;
    QTreeWidgetItem *tilesetRoot;

    ObjectNode *currentSelection;

    int GetItemID(QTreeWidgetItem *item);
    QTreeWidgetItem *GetItem(int ID);
    QTreeWidgetItem *AddNode(QTreeWidgetItem *parent, QString name, QString icon, int ID = 0);
    void RemoveChildrenNodes(QTreeWidgetItem *parent);
    
    QHash<int,QTreeWidgetItem*> itemHash;
};

#endif // RESOURCEVIEW_H
