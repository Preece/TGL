#ifndef LEVELPROPERTIESDIALOG_H
#define LEVELPROPERTIESDIALOG_H

#include <QDialog>
#include "Model/ResourceController.h"

namespace Ui {
class LevelPropertiesDialog;
}

class LevelPropertiesDialog : public QDialog
{
    Q_OBJECT

    ResourceController *resourceController;
    
public:
    explicit LevelPropertiesDialog(QWidget *parent = 0);
    ~LevelPropertiesDialog();

    void RegisterResourceController(ResourceController *newRM) {resourceController = newRM; }void on_mapNameInput_textChanged(const QString &arg1);

    void LoadValues();
    
private slots:

    void on_buttonBox_accepted();

private:
    Ui::LevelPropertiesDialog *ui;
};

#endif // LEVELPROPERTIES_H
