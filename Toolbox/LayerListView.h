#ifndef LAYERLISTVIEW_H
#define LAYERLISTVIEW_H

#include <QTableWidget>

#include "../Model/ResourceManager.h"

class LayerListView : public QTableWidget
{
    Q_OBJECT
public:
    explicit LayerListView(QWidget *parent = 0);

    void RegisterResourceManager(ResourceManager *rm) { resources = rm; }
signals:
    void LayerSelectionChanged(int newLayer);

public slots:
    void AddLayer();
    void RemoveLayer();

private:
    ResourceManager *resources;
};

#endif // LAYERLISTVIEW_H
