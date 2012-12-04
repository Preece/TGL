#ifndef RESOURCETAB_H
#define RESOURCETAB_H

#include <QTabWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>

#include "../SpriteEditor/SpriteEditor.h"
#include "../SpriteEditor/SpritesheetSelector.h"
#include "../ObjectEditor.h"
#include "../LevelEditor/TileItem.h"
#include "../Model/Tile.h"
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
    void RegisterTileSelector(QGraphicsScene *tiles);

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

    void RepopulateTileSelector();

private slots:

    void on_addImageButton_clicked();
    void on_viewImageButton_clicked();
    void on_deleteImageButton_clicked();
    void on_editSpriteButton_clicked();
    void on_addSpriteButton_clicked();
    void on_addObjectButton_clicked();
    void on_editObjectButton_clicked();
    void on_selectTilesetButton_clicked();

signals:
    void NewSpriteButtonClicked();
    void NewObjectButtonClicked();

private:
    Ui::ResourceTab *ui;

    ImageViewer *imageViewer;
    SpriteEditor *spriteWindow;
    ObjectEditor *objectEditorWindow;

    ResourceManager *resourceManager;

    //will eventually be a list of QTWI's
    QTreeWidgetItem *NPCTree;
    QTreeWidgetItem *EnemyTree;
    QTreeWidgetItem *ItemTree;
    QTreeWidgetItem *DoodadTree;

    QImage *spritesheet;
    QGraphicsScene *tileSelector;
};

#endif // RESOURCETAB_H
