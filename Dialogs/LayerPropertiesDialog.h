#ifndef LAYERPROPERTIES_H
#define LAYERPROPERTIES_H

#include <QDialog>

#include "../Model/TileLayer.h"

namespace Ui {
class LayerPropertiesDialog;
}

class LayerPropertiesDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit LayerPropertiesDialog(QWidget *parent = 0);
    ~LayerPropertiesDialog();

    int SetupNewLayer(TileLayer *newLayer);
    int EditLayer(TileLayer *newLayer);
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::LayerPropertiesDialog *ui;

    TileLayer *currentLayer;
};

#endif // LAYERPROPERTIES_H
