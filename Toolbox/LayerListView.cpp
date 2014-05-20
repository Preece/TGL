#include "LayerListView.h"

LayerListView::LayerListView(QWidget *parent) :
    QTableWidget(parent)
{
    resources = NULL;

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(SelectionUpdated()));
    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(UpdateItem(QTableWidgetItem*)));
    connect(this, SIGNAL(cellClicked(int,int)), this, SLOT(HandleClick(int,int)));

    //verticalHeader()->setMovable(true);
}

void LayerListView::RegisterResourceController(ResourceController *rm)
{
    resources = rm;
}

void LayerListView::RefreshNames()
{
    for(int i = 0; i < nameItems.count(); i++)
    {
        int itemID = nameItems[i]->data(Qt::UserRole).toInt();
        nameItems[i]->setText(resources->GetResource(itemID)->GetProperty("Name").toString());
    }
}

int LayerListView::GetSelectedID()
{
    int selectedID = 0;

    for(int i = 0; i < selectedItems().count(); i++)
    {
        if(!selectedItems()[i]->data(Qt::UserRole).isNull())
            selectedID = selectedItems()[i]->data(Qt::UserRole).toInt();
    }

    return selectedID;
}

void LayerListView::UpdateItem(QTableWidgetItem *item)
{
    if(!item->data(Qt::UserRole).isNull())
    {
        int selectedID = item->data(Qt::UserRole).toInt();

        ResourceNode *resource = resources->GetResource(selectedID);
        resource->SetProperty("Name", item->text());
    }
}

void LayerListView::AddLayer(int ID)
{
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
    for(int i = 0; i < nameItems.count(); i++)
    {
        if(nameItems[i]->data(Qt::UserRole).toInt() == ID)
        {
            removeRow(nameItems[i]->row());
            //delete nameItems[i];
            nameItems.removeAt(i);
            return;
        }
    }
}

void LayerListView::SelectionUpdated()
{
    emit LayerSelectionChanged(GetSelectedID());
}

void LayerListView::HandleClick(int row, int column)
{
    if(column == 0)
    {
        int corrID = item(row, 1)->data(Qt::UserRole).toInt();

        ResourceNode *tempResource = resources->GetResource(corrID);

        if(tempResource)
        {
            if(tempResource->GetProperty("Visible").toBool())
                tempResource->SetProperty("Visible", false);
            else
                tempResource->SetProperty("Visible", true);

            emit LayerVisibilityChanged(corrID, tempResource->GetProperty("Visible").toBool());
        }
    }
}
