#ifndef LAYERPROPERTIES_H
#define LAYERPROPERTIES_H

#include <QDialog>

#include "../Model/TileLayer.h"

namespace Ui {
class LayerProperties;
}

class LayerProperties : public QDialog
{
    Q_OBJECT
    
public:
    explicit LayerProperties(QWidget *parent = 0);
    ~LayerProperties();

    void NewLayer(TileLayer *newLayer);
    void EditLayer(TileLayer *newLayer);
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::LayerProperties *ui;

    TileLayer *currentLayer;
};

#endif // LAYERPROPERTIES_H
