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
    LevelProperties.cpp \
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
    SpriteEditor/AnimationPreviewer/AnimatedLabel.cpp
  

HEADERS  += \
    Model/Sprite.h \
    Model/ObjectPrototype.h \
    Model/ObjectInstance.h \
    Model/Animation.h \
    Model/Frame.h \
    Model/Savable.h \
    Model/ResourceManager.h \
    SpriteEditor/AnimationListItem.h \
    LevelProperties.h \
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
    SpriteEditor/AnimationPreviewer/AnimatedLabel.h
   

FORMS    += \
    ResourceTab/ResourceTab.ui \
    ResourceTab/ImageViewer.ui \
    SpriteEditor/SpriteEditor.ui \
    SpriteEditor/AnimationEditor.ui \
    LevelProperties.ui \
    MainWindow.ui \
    ObjectEditor.ui \
    SpriteEditor/SpritesheetSelector.ui \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.ui

RESOURCES += \
    Icons.qrc
