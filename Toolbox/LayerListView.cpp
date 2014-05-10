#include "LayerListView.h"

LayerListView::LayerListView(QWidget *parent) :
    QTableWidget(parent)
{
    resources = NULL;

    connect(this, SIGNAL(itemSelectionChanged()), this, SLOT(SelectionUpdated()));
}

void LayerListView::AddLayer(int ID)
{
    ObjectNode *layer = resources->GetObject(ID);

    insertRow(0);

    QTableWidgetItem *newIcon = new QTableWidgetItem(QIcon(":/Icons/addvalue.png"), "V");
    setItem(0, 0, newIcon);

    QTableWidgetItem *newItem = new QTableWidgetItem("New Layer");
    newItem->setData(Qt::UserRole, ID);
    setItem(0, 1, newItem);
}

void LayerListView::RemoveLayer(int ID)
{
    if(selectedItems().count() > 0)
    {
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
