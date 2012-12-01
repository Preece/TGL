#ifndef LEVELPROPERTIESDIALOG_H
#define LEVELPROPERTIESDIALOG_H

#include <QDialog>
#include "Model/ResourceManager.h"

namespace Ui {
class LevelPropertiesDialog;
}

class LevelPropertiesDialog : public QDialog
{
    Q_OBJECT

    ResourceManager *resourceManager;
    
public:
    explicit LevelPropertiesDialog(QWidget *parent = 0);
    ~LevelPropertiesDialog();

    void RegisterResourceManager(ResourceManager *newRM) {resourceManager = newRM; }void on_mapNameInput_textChanged(const QString &arg1);

    void LoadValues();
    
private slots:
    void on_tileSizeX_valueChanged(int arg1);

    void on_tileSizeY_valueChanged(int arg1);

    void on_mapSizeX_valueChanged(int arg1);

    void on_mapSizeY_valueChanged(int arg1);

private:
    Ui::LevelPropertiesDialog *ui;
};

#endif // LEVELPROPERTIES_H
