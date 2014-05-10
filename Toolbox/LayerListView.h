#ifndef LAYERLISTVIEW_H
#define LAYERLISTVIEW_H

#include <QTableWidget>

class LayerListView : public QTableWidget
{
    Q_OBJECT
public:
    explicit LayerListView(QWidget *parent = 0);

signals:
    void LayerSelectionChanged(int newLayer);

public slots:
    void AddLayer(int layerID);
    void RemoveLayer(int layerID);

};

#endif // LAYERLISTVIEW_H
