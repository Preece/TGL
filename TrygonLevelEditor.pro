#-------------------------------------------------
#
# Project created by QtCreator 2012-11-05T20:41:59
#
#-------------------------------------------------

QT       += core gui

TARGET = TrygonLevelEditor
TEMPLATE = app


SOURCES += main.cpp\
    Model/Frame.cpp \
    Model/Sprite.cpp \
    Model/Animation.cpp \
    Model/ResourceManager.cpp \
    Model/Savable.cpp \
    SpriteEditor/AnimationListItem.cpp \
    ObjectEditor.cpp \
    MainWindow.cpp \
    SpriteEditor/SpriteEditor.cpp \
    SpriteEditor/AnimationEditor.cpp \
    SpriteEditor/FrameListItem.cpp \
    ResourceTab/ResourceTab.cpp \
    Model/Image.cpp \
    ResourceTab/ImageSelectorItem.cpp \
    ResourceTab/ImageViewer.cpp \
    SpriteEditor/SpritesheetSelector.cpp \
    SpriteEditor/SelectionGraphicsScene.cpp \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.cpp \
    SpriteEditor/AnimationPreviewer/AnimatedLabel.cpp \
    ResourceTab/SpriteSelectorItem.cpp \
    Model/ObjectPrototype.cpp \
    ResourceTab/ObjectSelectorItem.cpp \
    LevelEditor/TileItem.cpp \
    LevelEditor/ObjectItem.cpp \
    LevelEditor/LayerManager.cpp \
    Commands/ModifyTilesCommand.cpp \
    Commands/AddObjectInstanceCommand.cpp \
    Commands/DeleteObjectInstanceCommand.cpp \
    Commands/AddObjectCommand.cpp \
    Commands/DeleteObjectCommand.cpp \
    Commands/AddSpriteCommand.cpp \
    Commands/DeletesSriteCommand.cpp \
    Model/Tile.cpp \
    LevelEditor/Brushes/TileBrush.cpp \
    Model/LevelProperties.cpp \
    LevelPropertiesDialog.cpp \
    Model/Layer.cpp \
    Model/Exporter.cpp \
    Model/TileInstance.cpp \
    LevelEditor/LayerGroup.cpp \
    LevelEditor/TileInstanceItem.cpp \
    LevelEditor/Brushes/PencilBrush.cpp \
    LevelEditor/Brushes/FillBrush.cpp \
    LevelEditor/Brushes/SmartBrush.cpp \
    LevelEditor/Brushes/EraserBrush.cpp \
    LevelEditor/LayerProperties.cpp \
    LevelEditor/Brushes/BrushPropertiesWidget.cpp
  

HEADERS  += \
    Model/Sprite.h \
    Model/ObjectPrototype.h \
    Model/ObjectInstance.h \
    Model/Animation.h \
    Model/Frame.h \
    Model/Savable.h \
    Model/ResourceManager.h \
    SpriteEditor/AnimationListItem.h \
    MainWindow.h \
    ObjectEditor.h \
    SpriteEditor/SpriteEditor.h \
    SpriteEditor/AnimationEditor.h \ 
    SpriteEditor/FrameListItem.h \
    ResourceTab/ResourceTab.h \
    Model/Image.h \
    ResourceTab/ImageSelectorItem.h \
    ResourceTab/ImageViewer.h \
    SpriteEditor/SpritesheetSelector.h \
    SpriteEditor/SelectionGraphicsScene.h \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.h \
    SpriteEditor/AnimationPreviewer/AnimatedLabel.h \
    ResourceTab/SpriteSelectorItem.h \
    ResourceTab/ObjectSelectorItem.h \
    LevelEditor/TileItem.h \
    LevelEditor/ObjectItem.h \
    LevelEditor/LayerManager.h \
    Commands/ModifyTilesCommand.h \
    Commands/AddObjectInstanceCommand.h \
    Commands/DeleteObjectInstanceCommand.h \
    Commands/AddObjectCommand.h \
    Commands/DeleteObjectCommand.h \
    Commands/AddSpriteCommand.h \
    Commands/DeleteSpriteCommand.h \
    Model/Tile.h \
    LevelEditor/Brushes/TileBrush.h \
    Model/LevelProperties.h \
    LevelPropertiesDialog.h \
    Model/Layer.h \
    Model/Exporter.h \
    Model/TileInstance.h \
    LevelEditor/LayerGroup.h \
    LevelEditor/TileInstanceItem.h \
    LevelEditor/Brushes/PencilBrush.h \
    LevelEditor/Brushes/FillBrush.h \
    LevelEditor/Brushes/SmartBrush.h \
    LevelEditor/Brushes/EraserBrush.h \
    LevelEditor/LayerProperties.h \
    LevelEditor/Brushes/BrushPropertiesWidget.h
   

FORMS    += \
    ResourceTab/ResourceTab.ui \
    ResourceTab/ImageViewer.ui \
    SpriteEditor/SpriteEditor.ui \
    SpriteEditor/AnimationEditor.ui \
    MainWindow.ui \
    ObjectEditor.ui \
    SpriteEditor/SpritesheetSelector.ui \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.ui \
    LevelPropertiesDialog.ui \
    LevelEditor/LayerProperties.ui \
    LevelEditor/Brushes/BrushPropertiesWidget.ui

RESOURCES += \
    Icons.qrc

OTHER_FILES += \
    Icons/zoomout.png \
    Icons/zoomin.png \
    Icons/zoom.png \
    Icons/selector.png \
    Icons/save.png \
    Icons/renderspot.png \
    Icons/previousframe.png \
    Icons/play.png \
    Icons/pencil.png \
    Icons/pause.png \
    Icons/open.png \
    Icons/nextframe.png \
    Icons/new.png \
    Icons/MissingFile.png \
    Icons/hotspot.png \
    Icons/frameselect.png \
    Icons/eyedropper.png \
    Icons/eraser.png \
    Icons/bucket.png \
    Icons/autoframeselect.png
