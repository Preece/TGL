#ifndef RESOURCETAB_H
#define RESOURCETAB_H

#include <QTabWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>

#include "../SpriteEditor/SpriteEditor.h"
#include "../SpriteEditor/SpritesheetSelector.h"
#include "TileWidgetItem.h"
#include "ImageViewer.h"
#include "ImageListWidgetItem.h"
#include "SpriteListWidgetItem.h"
#include "TileSelectorScene.h"

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
    void RegisterTileSelector(TileSelectorScene *tiles);

    void RepopulateImageSelector();
    void RepopulateLinkSelector();

    bool IsImageSelected();
    ImageListWidgetItem *GetSelectedImageItem();
    Image *GetSelectedImage();

private slots:

    void on_addImageButton_clicked();
    void on_viewImageButton_clicked();
    void on_deleteImageButton_clicked();

signals:

private:
    Ui::ResourceTab *ui;

    ImageViewer *imageViewer;

    ResourceManager *resourceManager;

    QImage *spritesheet;
    TileSelectorScene *tileSelector;
};

#endif // RESOURCETAB_H
