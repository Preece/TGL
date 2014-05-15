#ifndef LAYERLISTVIEW_H
#define LAYERLISTVIEW_H

#include <QTableWidget>
#include <QHeaderView>
#include <QList>

#include "../Model/ResourceController.h"

class LayerListView : public QTableWidget
{
    Q_OBJECT
public:
    explicit LayerListView(QWidget *parent = 0);

    void RegisterResourceController(ResourceController *rm);

    void RefreshNames();

    int GetSelectedID();

signals:
    void LayerSelectionChanged(int newLayer);
    void LayerVisibilityChanged(int layerID, bool visible);

public slots:
    void AddLayer(int ID);
    void RemoveLayer(int ID);

    void SelectionUpdated();
    void UpdateItem(QTableWidgetItem* item);

    void HandleClick(int row, int column);

private:
    QList<QTableWidgetItem*> nameItems;
    ResourceController *resources;
};

#endif // LAYERLISTVIEW_H
