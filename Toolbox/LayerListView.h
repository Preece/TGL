#ifndef LAYERLISTVIEW_H
#define LAYERLISTVIEW_H

#include <QTableWidget>
#include <QHeaderView>

#include "../Model/ResourceController.h"

class LayerListView : public QTableWidget
{
    Q_OBJECT
public:
    explicit LayerListView(QWidget *parent = 0);

    void RegisterResourceManager(ResourceController *rm) { resources = rm; }

signals:
    void LayerSelectionChanged(int newLayer);

public slots:
    void AddLayer(int ID);
    void RemoveLayer(int ID);

    void SelectionUpdated();

    void cellClicked(int row, int column);

private:
    ResourceController *resources;
};

#endif // LAYERLISTVIEW_H
