#include "ResourceView.h"

ResourceView::ResourceView(QWidget *parent) :
    QTreeWidget(parent)
{
    resources = NULL;
    currentSelection = 0;

    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(selectionUpdated(QTreeWidgetItem*,int)));

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
}

void ResourceView::RepopulateEverything()
{
    RepopulateLayers();
}

void ResourceView::RepopulateLayers()
{
    //get rid of the children
    RemoveChildrenNodes(layerRoot);

    //get each layer and add it as a child node of the layer root
    for(int i = 0; i < resources->GetLayerCount(); i++)
    {
        //fetch the layer from the model
        TileLayer *layer = resources->GetLayerByIndex(i);

        QTreeWidgetItem *newLayerNode = AddNode(layerRoot, layer->GetName(), ":/Icons/Icons/save.png", layer->GetID());

        //if this layer was the current selection, select it again
        if(layer->GetID() == currentSelection)
        {
            newLayerNode->setSelected(true);
            layerRoot->setExpanded(true);
        }
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

bool ResourceView::IsLayerSelected()
{
    //if anything is selected
    if(resources->GetTileLayer(GetSelectedID()))
        return true;

    return false;
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

void ResourceView::RemoveChildrenNodes(QTreeWidgetItem *parent)
{
    if(!parent)
        return;

    //loop from the last item to the first, deleting them
    for(int i = (parent->childCount()); i >= 0; i--)
    {
        if(parent->child(i))
            delete parent->child(i);
    }
}


void ResourceView::selectionUpdated(QTreeWidgetItem *item, int column)
{
    int selectedID = GetSelectedID();

    //get the ID from the selection
    if(selectedID)
    {
        //store the selection
        currentSelection = selectedID;

        //if the new selection is a layer, broadcast the change
        if(resources->GetTileLayer(selectedID))
            emit NewLayerSelected(selectedID);
    }
    else
    {
        //if nothing is selected, zero out the current selection
        currentSelection = 0;
    }
}
