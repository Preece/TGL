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

    void on_buttonBox_accepted();

private:
    Ui::LevelPropertiesDialog *ui;
};

#endif // LEVELPROPERTIES_H
