#ifndef RESOURCETAB_H
#define RESOURCETAB_H

#include <QTabWidget>
#include <QFileDialog>
#include <QMessageBox>

#include "../SpriteEditor/SpriteEditor.h"
#include "../ObjectEditor.h"
#include "ImageViewer.h"
#include "ImageSelectorItem.h"
#include "SpriteSelectorItem.h"
#include "ObjectSelectorItem.h"

#include "../Model/ResourceManager.h"
#include "../Model/Image.h"

namespace Ui {
class ResourceTab;
}

class ResourceTab : public QTabWidget
{
    Q_OBJECT
    
public:
    explicit ResourceTab(QWidget *parent = 0);
    ~ResourceTab();

    void RegisterResourceManager(ResourceManager *newResourceManager) { resourceManager = newResourceManager; }
    
    void RepopulateTileSelector();
    void RepopulateObjectSelector();
    void RepopulateSpriteSelector();
    void RepopulateImageSelector();
    void RepopulateLinkSelector();

    bool IsImageSelected();
    ImageSelectorItem *GetSelectedImageItem();
    Image *GetSelectedImage();

    bool IsSpriteSelected();
    SpriteSelectorItem *GetSelectedSpriteItem();
    Sprite *GetSelectedSprite();

    bool IsObjectSelected();
    ObjectSelectorItem *GetSelectedObjectItem();
    ObjectPrototype *GetSelectedObject();

private slots:
    void on_addImageButton_clicked();

    void on_viewImageButton_clicked();

    void on_deleteImageButton_clicked();

    void on_editSpriteButton_clicked();

    void on_addSpriteButton_clicked();

    void on_addObjectButton_clicked();

    void on_editObjectButton_clicked();

signals:
    void NewSpriteButtonClicked();
    void NewObjectButtonClicked();

private:
    Ui::ResourceTab *ui;

    ImageViewer *imageViewer;
    SpriteEditor *spriteWindow;
    ObjectEditor *objectEditorWindow;

    ResourceManager *resourceManager;
};

#endif // RESOURCETAB_H
