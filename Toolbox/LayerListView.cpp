#include "LayerListView.h"

LayerListView::LayerListView(QWidget *parent) :
    QTableWidget(parent)
{
    resources = NULL;

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(SelectionUpdated()));
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(UpdateItem(QTableWidgetItem*)));
    connect(this, SIGNAL(cellClicked(int,int)), this, SLOT(HandleClick(int,int)));
}

void LayerListView::RegisterResourceController(ResourceController *rm)
{
    resources = rm;


    connect(resources, SIGNAL(LayerRemoved(int)), this, SLOT(RemoveLayer(int)));
}

void LayerListView::RefreshNames()
{
    for(int i = 0; i < nameItems.count(); i++)
    {
        int itemID = nameItems[i]->data(Qt::UserRole).toInt();
        nameItems[i]->setText(resources->GetObject(itemID)->GetProperty("Name").toString());
    }
}

void LayerListView::UpdateItem(QTableWidgetItem *item)
{
    if(!item->data(Qt::UserRole).isNull())
    {
        int selectedID = item->data(Qt::UserRole).toInt();

        ResourceNode *resource = resources->GetObject(selectedID);
        resource->SetProperty("Name", item->text());
    }
}

void LayerListView::AddLayer(int ID)
{
    ResourceNode *layer = resources->GetObject(ID);

    insertRow(0);

    QTableWidgetItem *newIcon = new QTableWidgetItem(QIcon(":/Icons/addvalue.png"), QString());
    newIcon->setFlags(newIcon->flags() & ~(Qt::ItemIsDropEnabled));
    newIcon->setFlags(newIcon->flags() & (~Qt::ItemIsEditable));
    setItem(0, 0, newIcon);

    QTableWidgetItem *newItem = new QTableWidgetItem("New Layer");
    newItem->setData(Qt::UserRole, ID);
    newItem->setFlags(newItem->flags() & ~(Qt::ItemIsDropEnabled));
    setItem(0, 1, newItem);

    selectRow(0);
    emit LayerSelectionChanged(ID);

    nameItems.push_back(newItem);
}

void LayerListView::RemoveLayer(int ID)
{
    if(selectedItems().count() > 0)
    {
        nameItems.removeAll(selectedItems()[0]);
        removeRow(selectedItems()[0]->row());
    }
}

void LayerListView::SelectionUpdated()
{
    int selectedID;

    for(int i = 0; i < selectedItems().count(); i++)
    {
        if(!selectedItems()[i]->data(Qt::UserRole).isNull())
            selectedID = selectedItems()[i]->data(Qt::UserRole).toInt();
    }

    emit LayerSelectionChanged(selectedID);
}

void LayerListView::HandleClick(int row, int column)
{
    if(column == 0)
    {
        int corrID = item(row, 1)->data(Qt::UserRole).toInt();

        ResourceNode *object = resources->GetObject(corrID);

        if(object)
        {
            if(object->GetProperty("Visible").toBool())
                object->SetProperty("Visible", false);
            else
                object->SetProperty("Visible", true);

            emit LayerVisibilityChanged(corrID, object->GetProperty("Visible").toBool());
        }
    }
}
