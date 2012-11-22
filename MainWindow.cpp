#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //zero out these pointers
    spriteWindow = 0;
    levelPropertiesWindow = 0;
    objectEditorWindow = 0;

    //create a resource manager
    resources = new ResourceManager;

    //register the resource manager with the resource tab. The resource tab will
    //keep itself in synch with the resource manager
    ui->resourceTab->RegisterResourceManager(resources);
}

MainWindow::~MainWindow()
{
    delete ui;

    resources->DestroyAllResources();
    delete resources;
}

void MainWindow::on_actionProperties_triggered()
{
    if(!levelPropertiesWindow)
    {
        levelPropertiesWindow = new LevelProperties;
    }

    levelPropertiesWindow->show();
}

void MainWindow::on_actionAdd_Sprite_triggered()
{
    //create the sprite editing window if it does not already exist
    if(!spriteWindow)
    {
        spriteWindow = new SpriteEditor;
        spriteWindow->RegisterResourceManager(resources);
    }

    //create a temporary sprite for the dialog to operate upon
    Sprite *temporarySprite = new Sprite;

    //pass the temporary sprite to the dialog
    spriteWindow->NewSprite(temporarySprite);

    //add the sprite to the resource manager if the dialog is accepted
    if(spriteWindow->exec() == QDialog::Accepted)
    {
        resources->AddSprite(temporarySprite);
    }
    //delete the temporary sprite if the dialog is rejected
    else
    {
        delete temporarySprite;
    }
}

void MainWindow::on_actionAdd_Object_triggered()
{
    if(!objectEditorWindow)
    {
        objectEditorWindow = new ObjectEditor;
    }

    objectEditorWindow->show();
}
