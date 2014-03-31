#include "ResourceView.h"

ResourceView::ResourceView(QWidget *parent) :
    QTreeWidget(parent)
{
    resources = NULL;
}

void ResourceView::RepopulateEverything()
{
    //clear out all the items that exist now
    this->clear();

    //create and add a root node for the project
    QTreeWidgetItem *projectRoot = new QTreeWidgetItem;
    projectRoot->setText(0, "Project Root");
    projectRoot->setIcon(0, QIcon(":/Icons/Icons/open.png"));
    addTopLevelItem(projectRoot);
    projectRoot->setExpanded(true);

    //add children nodes for each of the types of objects
    QTreeWidgetItem *layerRoot = new QTreeWidgetItem;
    layerRoot->setText(0, "Layers");
    layerRoot->setIcon(0, QIcon(":/Icons/Icons/open.png"));
    projectRoot->addChild(layerRoot);

    QTreeWidgetItem *imageRoot = new QTreeWidgetItem;
    imageRoot->setText(0, "Images");
    imageRoot->setIcon(0, QIcon(":/Icons/Icons/open.png"));
    projectRoot->addChild(imageRoot);

    QTreeWidgetItem *spriteRoot = new QTreeWidgetItem;
    spriteRoot->setText(0, "Sprites");
    spriteRoot->setIcon(0, QIcon(":/Icons/Icons/open.png"));
    projectRoot->addChild(spriteRoot);

    QTreeWidgetItem *tilesetRoot = new QTreeWidgetItem;
    tilesetRoot->setText(0, "Tilesets");
    tilesetRoot->setIcon(0, QIcon(":/Icons/Icons/open.png"));
    projectRoot->addChild(tilesetRoot);

    //get each layer and add it as a child node of the layer root
    for(int i = 0; i < resources->GetLayerCount(); i++)
    {
        //fetch the layer from the model
        TileLayer *layer = resources->GetLayerByIndex(i);

        //create a new tree widget item
        QTreeWidgetItem *newLayerItem = new QTreeWidgetItem;

        //use the layers name as the item text
        newLayerItem->setText(0, layer->GetName());

        //and store the ID of the layer
        newLayerItem->setData(0, Qt::UserRole, QVariant(layer->GetID()));

        //add the new item as a child of the layer root
        layerRoot->addChild(newLayerItem);
    }
}

int ResourceView::GetSelectedID()
{
    QList<QTreeWidgetItem*> selectedItem = selectedItems();

    if(selectedItem.count() > 0)
    {
        return GetItemID(selectedItem[0]);
    }

    return 0;
}

int ResourceView::GetItemID(QTreeWidgetItem *item)
{
    if(item)
    {
        QVariant id = item->data(0, Qt::UserRole);
        return id.toInt();
    }

    return 0;
}
