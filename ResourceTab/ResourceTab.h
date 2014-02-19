#ifndef RESOURCETAB_H
#define RESOURCETAB_H

#include <QTabWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>

#include "../SpriteEditor/SpriteEditor.h"
#include "../SpriteEditor/SpritesheetSelector.h"
#include "TileWidgetItem.h"
#include "../Model/Tile.h"
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

    void RepopulateSpriteSelector();
    void RepopulateImageSelector();
    void RepopulateLinkSelector();

    bool IsImageSelected();
    ImageListWidgetItem *GetSelectedImageItem();
    Image *GetSelectedImage();

    bool IsSpriteSelected();
    SpriteListWidgetItem *GetSelectedSpriteItem();
    Sprite *GetSelectedSprite();

    void RepopulateTileSelector();

private slots:

    void on_addImageButton_clicked();
    void on_viewImageButton_clicked();
    void on_deleteImageButton_clicked();

    void on_editSpriteButton_clicked();
    void on_addSpriteButton_clicked();
    void on_deleteSpriteButton_clicked();

    void on_selectTilesetButton_clicked();


signals:
    void NewSpriteButtonClicked();

private:
    Ui::ResourceTab *ui;

    ImageViewer *imageViewer;
    SpriteEditor *spriteWindow;

    ResourceManager *resourceManager;

    QImage *spritesheet;
    TileSelectorScene *tileSelector;
};

#endif // RESOURCETAB_H
