#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>

#include "Model/Sprite.h"
#include "Model/ObjectInstance.h"
#include "Model/ObjectPrototype.h"
#include "Model/resourcemanager.h"

#include "SpriteEditor/SpriteEditor.h"
#include "LevelProperties.h"
#include "ObjectEditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_actionProperties_triggered();
    void on_actionAdd_Sprite_triggered();
    void on_actionAdd_Object_triggered();

private:
    Ui::MainWindow *ui;

    //Dialogs
    SpriteEditor *spriteWindow;
    LevelProperties *levelPropertiesWindow;
    ObjectEditor *objectEditorWindow;

    ResourceManager *resources;
};

#endif // MAINWINDOW_H
