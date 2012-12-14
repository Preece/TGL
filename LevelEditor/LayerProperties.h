#ifndef LAYERPROPERTIES_H
#define LAYERPROPERTIES_H

#include <QDialog>

namespace Ui {
class LayerProperties;
}

class LayerProperties : public QDialog
{
    Q_OBJECT
    
public:
    explicit LayerProperties(QWidget *parent = 0);
    ~LayerProperties();
    
private:
    Ui::LayerProperties *ui;
};

#endif // LAYERPROPERTIES_H
