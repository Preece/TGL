#include "LayerListView.h"

LayerListView::LayerListView(QWidget *parent) :
    QTableWidget(parent)
{
}

void LayerListView::AddLayer()
{
    insertRow(0);

    QTableWidgetItem *newIcon = new QTableWidgetItem(QIcon(":/Icons/addvalue.png"), "Visible");
    setItem(0, 0, newIcon);

    QTableWidgetItem *newItem = new QTableWidgetItem("New Layer");
    setItem(0, 1, newItem);
}

void LayerListView::RemoveLayer()
{
    if(selectedItems().count() > 0)
        removeRow(selectedItems()[0]->row());
}
