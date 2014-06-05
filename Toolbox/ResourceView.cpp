#include "ResourceView.h"

ResourceView::ResourceView(QWidget *parent) :
    QTreeWidget(parent)
{
    resources = NULL;
    currentSelection = 0;

    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(selectionUpdated(QTreeWidgetItem*,int)));

    //create and add a root node for the project
    projectRoot = new QTreeWidgetItem;
    projectRoot->setText(0, "Project Root");
    projectRoot->setIcon(0, QIcon(":/Icons/open.png"));
    addTopLevelItem(projectRoot);
    projectRoot->setExpanded(true);

    //add children nodes for each of the types of resources
    layerRoot = AddNode(projectRoot, "Layer", ":/Icons/open.png");
    imageRoot = AddNode(projectRoot, "Images", ":/Icons/open.png");
    tilesetRoot = AddNode(projectRoot, "Tilesets", ":/Icons/open.png");
    miscRoot = AddNode(projectRoot, "Miscellaneous", ":/Icons/open.png");
}

void ResourceView::RegisterResourceController(ResourceController *rm)
{
    resources = rm;
    connect(resources, SIGNAL(ResourceAdded(int)), this, SLOT(AddResource(int)));
    connect(resources, SIGNAL(ResourceDeleted(int)), this, SLOT(RemoveResource(int)));
}

void ResourceView::RepopulateEverything()
{
    //store the level properties ID in the project root
    if(resources)
        projectRoot->setData(0, Qt::UserRole, QVariant(resources->GetLevelProperties()->GetID()));
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

void ResourceView::RefreshNames()
{
    QList<QTreeWidgetItem*> items = itemHash.values();

    for(int i = 0; i < items.count(); i++)
    {
        ResourceNode *res = resources->GetResource(items[i]->data(0, Qt::UserRole).toInt());

        if(res)
            items[i]->setText(0, res->GetProperty("Name").toString());
    }

    if(currentSelection)
        emit NewResourceSelected(currentSelection);
}

void ResourceView::ClearEverything()
{
    RemoveChildrenNodes(layerRoot);
    RemoveChildrenNodes(imageRoot);
    RemoveChildrenNodes(tilesetRoot);
    RemoveChildrenNodes(miscRoot);
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

QTreeWidgetItem *ResourceView::GetItem(int ID)
{
    if(itemHash.contains(ID))
        return itemHash[ID];

    return NULL;
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


void ResourceView::selectionUpdated(QTreeWidgetItem *, int)
{
    ResourceNode *selectedResource = resources->GetResource(GetSelectedID());

    if(selectedResource)
    {
        emit NewResourceSelected(selectedResource);
        currentSelection = selectedResource;
    }
    else
    {
        //if nothing is selected, zero out the current selection
        currentSelection = NULL;
    }
}

void ResourceView::AddResource(int ID)
{
    ResourceNode *newResource = resources->GetResource(ID);

    QString name = newResource->GetProperty("Name").toString();

    if(name.isEmpty())
        name = "New Resource";

    switch(newResource->GetType())
    {
    case UnknownType:
        itemHash[ID] = AddNode(miscRoot, name, ":/Icons/save.png", ID);
        break;

    case ImageType:
        itemHash[ID] = AddNode(imageRoot, name, ":/Icons/save.png", ID);
        break;

    case TileLayerType:
        itemHash[ID] = AddNode(layerRoot, name, ":/Icons/save.png", ID);
        break;

    default:
        itemHash[ID] = AddNode(projectRoot, name, ":/Icons/save.png", ID);
    }


}

void ResourceView::RemoveResource(int ID)
{
    if(itemHash.contains(ID))
    {
        delete itemHash[ID];
        itemHash.remove(ID);
    }
}

void ResourceView::UpdateResourceName(int ID, QString name)
{
    QTreeWidgetItem *item = GetItem(ID);

    if(item)
        item->setText(0, name);
}
