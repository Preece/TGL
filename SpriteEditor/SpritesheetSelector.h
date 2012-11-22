#ifndef SPRITESHEETSELECTOR_H
#define SPRITESHEETSELECTOR_H

#include <QDialog>

#include "../Model/ResourceManager.h"
#include "../ResourceTab/ImageSelectorItem.h"

namespace Ui {
class SpritesheetSelector;
}

class SpritesheetSelector : public QDialog
{
    Q_OBJECT
    
public:
    explicit SpritesheetSelector(QWidget *parent = 0);
    ~SpritesheetSelector();

    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }
    void RepopulateImageList();
    Image *GetSelectedImage();

    bool IsImageSelected();

    void ClearImageList();
    
private slots:

    void on_imageList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::SpritesheetSelector *ui;

    ResourceManager *resourceManager;
    Image *selectedImage;

};

#endif // SPRITESHEETSELECTOR_H
