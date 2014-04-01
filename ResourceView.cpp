#include "ResourceView.h"

ResourceView::ResourceView(QWidget *parent) :
    QTreeWidget(parent)
{
    resources = NULL;

    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(selectionUpdated(QTreeWidgetItem*,int)));
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
    layerRoot = AddNode(projectRoot, "Layer", ":/Icons/Icons/open.png");
    imageRoot = AddNode(projectRoot, "Images", ":/Icons/Icons/open.png");
    spriteRoot = AddNode(projectRoot, "Sprites", ":/Icons/Icons/open.png");
    tilesetRoot = AddNode(projectRoot, "Tilesets", ":/Icons/Icons/open.png");

    //get each layer and add it as a child node of the layer root
    for(int i = 0; i < resources->GetLayerCount(); i++)
    {
        //fetch the layer from the model
        TileLayer *layer = resources->GetLayerByIndex(i);

        AddNode(layerRoot, layer->GetName(), ":/Icons/Icons/save.png", layer->GetID());
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

QTreeWidgetItem *ResourceView::AddNode(QTreeWidgetItem *parent, QString name, QString icon, int ID)
{
    QTreeWidgetItem *newNode = new QTreeWidgetItem;
    newNode->setText(0, name);
    newNode->setIcon(0, QIcon(icon));

    if(ID)
        newNode->setData(0, Qt::UserRole, QVariant(ID));

    parent->addChild(newNode);

    return newNode;
}


void ResourceView::selectionUpdated(QTreeWidgetItem *item, int column)
{
    int selectedID = GetSelectedID();

    //get the ID from the selection
    if(selectedID)
    {
        //if the new selection is a layer, update the selection in the layer manager
        if(resources->GetTileLayer(selectedID))
            emit NewLayerSelected(selectedID);
    }
}
