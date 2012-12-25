#ifndef SPRITEEDIT_H
#define SPRITEEDIT_H

#define FRAME_SELECT_TOOL       0
#define AUTO_FRAME_SELECT_TOOL  1
#define POINTER_TOOL            2
#define RENDER_SPOT_TOOL        3
#define HOTSPOT_TOOL            4
#define ZOOM_TOOL               5

#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "AnimationEditor.h"
#include "SpritesheetSelector.h"
#include "AnimationListItem.h"
#include "FrameListItem.h"
#include "SelectionGraphicsScene.h"
#include "AnimationPreviewer/AnimationPreviewer.h"
#include "Model/ResourceManager.h"
#include "Model/Sprite.h"

namespace Ui {
class SpriteEditor;
}

class SpriteEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit SpriteEditor(QWidget *parent = 0);
    ~SpriteEditor();

    void ClearAll();
    bool IsAnimationSelected();
    bool IsFrameSelected();
    bool IsSpritesheetLoaded() { return spritesheetLoaded; }

    AnimationListItem *GetSelectedAnimationItem();
    Animation *GetSelectedAnimation();
    FrameListItem *GetSelectedFrameItem();
    Frame *GetSelectedFrame();

    void SetFrameIcon(FrameListItem *frameListItem);

    void ClearFrameList();
    void RepopulateFrameList();

    void ChangeTool(int newTool);
    int GetCurrentTool();

    void UpdateDisplayImage();
    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }


    
private slots:

    void on_buttonBox_accepted();
    void on_addAnimationButton_clicked();
    void on_deleteAnimationButton_clicked();
    void on_editAnimationButton_clicked();
    void on_addFrameButton_clicked();
    void on_deleteFrameButton_clicked();
    void on_animationList_currentRowChanged();
    void on_frameList_currentRowChanged();
    void on_selectSpritesheetButton_clicked();
    void on_frameDelayInput_valueChanged();
    void on_zoominTool_clicked();
    void on_zoomoutTool_clicked();
    void on_spriteNameInput_textChanged(const QString &arg1);

    void on_previewButton_clicked();

public slots:
    void NewSprite(Sprite *newSprite);
    void EditSprite(Sprite *editSprite);

    void StoreNewFrameRect(QRect newRect);
    void StoreNewRenderSpot(QPoint newSpot);

    void UpdateToolSelection(int newTool);

private:
    Ui::SpriteEditor *ui;

    AnimationEditor *animationEditor;
    SpritesheetSelector *spritesheetSelector;
    AnimationPreviewer *animationPreviewer;

    Sprite *currentSprite;
    ResourceManager *resourceManager;

    int currentTool;
    float zoomLevel;
    bool spritesheetLoaded;

    SelectionGraphicsScene imageScene;
    QGraphicsPixmapItem *imageItem;
};

#endif // SPRITEEDIT_H
