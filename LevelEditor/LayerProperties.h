#ifndef LAYERPROPERTIES_H
#define LAYERPROPERTIES_H

#include <QDialog>

#include "../Model/Layer.h"

namespace Ui {
class LayerProperties;
}

class LayerProperties : public QDialog
{
    Q_OBJECT
    
public:
    explicit LayerProperties(QWidget *parent = 0);
    ~LayerProperties();

    void NewLayer(Layer *newLayer);
    void EditLayer(Layer *newLayer);
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::LayerProperties *ui;

    Layer *currentLayer;
};

#endif // LAYERPROPERTIES_H
