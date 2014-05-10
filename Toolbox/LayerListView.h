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
    void AddLayer();
    void RemoveLayer();

};

#endif // LAYERLISTVIEW_H
