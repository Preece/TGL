#ifndef RESOURCEVIEW_H
#define RESOURCEVIEW_H

#include <QTreeWidget>
#include <QString>

#include "Model/ResourceController.h"

class ResourceView : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ResourceView(QWidget *parent = 0);

    void RegisterResourceController(ResourceController *rm);
    void RepopulateEverything();
    int GetSelectedID();

    void paintEvent(QPaintEvent* e) { QTreeWidget::paintEvent(e); }

    void RefreshNames();
    
signals:
    void NewResourceSelected(ResourceNode *newObject);
    
public slots:
    void selectionUpdated(QTreeWidgetItem*, int);

    void AddResource(int ID);
    void RemoveResource(int ID);

    void UpdateResourceName(int ID, QString name);

private:
    ResourceController *resources;

    QTreeWidgetItem *projectRoot;
    QTreeWidgetItem *layerRoot;
    QTreeWidgetItem *imageRoot;
    QTreeWidgetItem *tilesetRoot;
    QTreeWidgetItem *miscRoot;

    ResourceNode *currentSelection;

    int GetItemID(QTreeWidgetItem *item);
    QTreeWidgetItem *GetItem(int ID);
    QTreeWidgetItem *AddNode(QTreeWidgetItem *parent, QString name, QString icon, int ID = 0);
    void RemoveChildrenNodes(QTreeWidgetItem *parent);
    
    QHash<int,QTreeWidgetItem*> itemHash;
};

#endif // RESOURCEVIEW_H
