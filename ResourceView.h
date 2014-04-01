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

    void RepopulateLayers();

    int GetSelectedID();
    
signals:
    void NewLayerSelected(int newID);
    
public slots:
    void selectionUpdated(QTreeWidgetItem *item, int column);

private:
    ResourceManager *resources;

    QTreeWidgetItem *layerRoot;
    QTreeWidgetItem *imageRoot;
    QTreeWidgetItem *spriteRoot;
    QTreeWidgetItem *tilesetRoot;

    int currentSelection;

    int GetItemID(QTreeWidgetItem *item);
    QTreeWidgetItem *AddNode(QTreeWidgetItem *parent, QString name, QString icon, int ID = 0);
    
};

#endif // RESOURCEVIEW_H
