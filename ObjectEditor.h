#ifndef OBJECTEDITOR_H
#define OBJECTEDITOR_H

#include <QDialog>
#include <QMap>
#include <QVariant>
#include <QTreeWidgetItem>

#include "Model/ObjectPrototype.h"
#include "Model/ResourceManager.h"
#include "ResourceTab/SpriteSelectorItem.h"

namespace Ui {
class ObjectEditor;
}

class ObjectEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit ObjectEditor(QWidget *parent = 0);
    ~ObjectEditor();

    void NewObject(ObjectPrototype *newObject);
    void EditObject(ObjectPrototype *newObject);

    void RepopulateSpriteList();
    void RepopulateCustomValueList();
    void UpdateSymbol();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }
    
private slots:
    void on_objectNameInput_textChanged(const QString &arg1);

    void on_objectTypeSelector_currentIndexChanged(int index);

    void on_spriteList_currentItemChanged(QListWidgetItem *current);

    void on_addCustomButton_clicked();

    void on_removeCustomButton_clicked();

    void on_customValues_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_buttonBox_accepted();

private:
    Ui::ObjectEditor *ui;

    ObjectPrototype *currentObject;

    ResourceManager *resourceManager;


};

#endif // OBJECTEDITOR_H
