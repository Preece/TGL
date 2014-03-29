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
    SpriteEditor/AnimationListItem.cpp \
    MainWindow.cpp \
    SpriteEditor/SpriteEditor.cpp \
    SpriteEditor/AnimationEditor.cpp \
    SpriteEditor/FrameListItem.cpp \
    ResourceTab/ResourceTab.cpp \
    Model/Image.cpp \
    ResourceTab/ImageViewer.cpp \
    SpriteEditor/SpritesheetSelector.cpp \
    SpriteEditor/SelectionGraphicsScene.cpp \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.cpp \
    SpriteEditor/AnimationPreviewer/AnimatedLabel.cpp \
    LevelEditor/LayerManager.cpp \
    Commands/ModifyTilesCommand.cpp \
    LevelEditor/Brushes/TileBrush.cpp \
    Model/LevelProperties.cpp \
    LevelPropertiesDialog.cpp \
    Model/Exporter.cpp \
    LevelEditor/Brushes/PencilBrush.cpp \
    LevelEditor/Brushes/FillBrush.cpp \
    LevelEditor/Brushes/SmartBrush.cpp \
    LevelEditor/Brushes/EraserBrush.cpp \
    LevelEditor/LayerProperties.cpp \
    LevelEditor/Brushes/BrushPropertiesWidget.cpp \
    LevelEditor/Brushes/ScatterBrush.cpp \
    LevelEditor/Brushes/BrushPropertiesWindow.cpp \
    LevelEditor/Brushes/ComplexBrush.cpp \
    Model/Exporters/PackedBinaryExporter.cpp \
    Commands/AddResourceCommand.cpp \
    Commands/DeleteResourceCommand.cpp \
    Commands/AddTilesCommand.cpp \
    LevelEditor/Brushes/ReplacerBrush.cpp \
    ResourceTab/TileSelectorView.cpp \
    ResourceTab/TileSelectorScene.cpp \
    LevelEditor/Brushes/StampBrush.cpp \
    LevelEditor/Brushes/LineBrush.cpp \
    LevelEditor/Brushes/MatrixBrush.cpp \
    ResourceTab/SpriteListWidgetItem.cpp \
    ResourceTab/ImageListWidgetItem.cpp \
    ResourceTab/TileWidgetItem.cpp \
    Model/TileLayer.cpp \
    LevelEditor/TileLayerView.cpp \
    Model/ItemNode.cpp
  

HEADERS  += \
    Model/Sprite.h \
    Model/Animation.h \
    Model/Frame.h \
    Model/ResourceManager.h \
    SpriteEditor/AnimationListItem.h \
    MainWindow.h \
    SpriteEditor/SpriteEditor.h \
    SpriteEditor/AnimationEditor.h \ 
    SpriteEditor/FrameListItem.h \
    ResourceTab/ResourceTab.h \
    Model/Image.h \
    ResourceTab/ImageViewer.h \
    SpriteEditor/SpritesheetSelector.h \
    SpriteEditor/SelectionGraphicsScene.h \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.h \
    SpriteEditor/AnimationPreviewer/AnimatedLabel.h \
    LevelEditor/LayerManager.h \
    Commands/ModifyTilesCommand.h \
    LevelEditor/Brushes/TileBrush.h \
    Model/LevelProperties.h \
    LevelPropertiesDialog.h \
    Model/Exporter.h \
    LevelEditor/Brushes/PencilBrush.h \
    LevelEditor/Brushes/FillBrush.h \
    LevelEditor/Brushes/SmartBrush.h \
    LevelEditor/Brushes/EraserBrush.h \
    LevelEditor/LayerProperties.h \
    LevelEditor/Brushes/BrushPropertiesWidget.h \
    LevelEditor/Brushes/ScatterBrush.h \
    LevelEditor/Brushes/BrushPropertiesWindow.h \
    LevelEditor/Brushes/ComplexBrush.h \
    Model/Exporters/PackedBinaryExporter.h \
    Commands/AddResourceCommand.h \
    Commands/DeleteResourceCommand.h \
    Commands/AddTilesCommand.h \
    LevelEditor/Brushes/ReplacerBrush.h \
    ResourceTab/TileSelectorView.h \
    ResourceTab/TileSelectorScene.h \
    LevelEditor/Brushes/StampBrush.h \
    LevelEditor/Brushes/LineBrush.h \
    LevelEditor/Brushes/MatrixBrush.h \
    ResourceTab/SpriteListWidgetItem.h \
    ResourceTab/ImageListWidgetItem.h \
    ResourceTab/TileWidgetItem.h \
    Model/TileLayer.h \
    LevelEditor/TileLayerView.h \
    Model/ItemNode.h
   

FORMS    += \
    ResourceTab/ResourceTab.ui \
    ResourceTab/ImageViewer.ui \
    SpriteEditor/SpriteEditor.ui \
    SpriteEditor/AnimationEditor.ui \
    MainWindow.ui \
    SpriteEditor/SpritesheetSelector.ui \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.ui \
    LevelPropertiesDialog.ui \
    LevelEditor/LayerProperties.ui \
    LevelEditor/Brushes/BrushPropertiesWidget.ui \
    LevelEditor/Brushes/BrushPropertiesWindow.ui

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
    Icons/autoframeselect.png \
    Icons/zoomout.png \
    Icons/zoomin.png \
    Icons/undo.png \
    Icons/size4.png \
    Icons/size3.png \
    Icons/size2.png \
    Icons/size1.png \
    Icons/selector.png \
    Icons/selectionbox.png \
    Icons/scatter.png \
    Icons/save.png \
    Icons/renderspot.png \
    Icons/removevalue.png \
    Icons/redo.png \
    Icons/previousframe.png \
    Icons/play.png \
    Icons/pencil.png \
    Icons/pause.png \
    Icons/open.png \
    Icons/nextframe.png \
    Icons/new.png \
    Icons/MissingFile.png \
    Icons/hotspot.png \
    Icons/grid.png \
    Icons/frameselect.png \
    Icons/eyedropper.png \
    Icons/eraser.png \
    Icons/bucket.png \
    Icons/brush.png \
    Icons/autoframeselect.png \
    Icons/addvalue.png \
    Icons/BrushGuides/toprightcorner.png \
    Icons/BrushGuides/topright.png \
    Icons/BrushGuides/topmiddle.png \
    Icons/BrushGuides/topleftcorner.png \
    Icons/BrushGuides/topleft.png \
    Icons/BrushGuides/middleright.png \
    Icons/BrushGuides/middleleft.png \
    Icons/BrushGuides/bottomrightcorner.png \
    Icons/BrushGuides/bottomright.png \
    Icons/BrushGuides/bottommiddle.png \
    Icons/BrushGuides/bottomleftcorner.png \
    Icons/BrushGuides/bottomleft.png \
    Icons/BrushGuides/middle.png \
    Icons/scatterfill.png \
    Icons/replacer.png \
    Icons/line.png \
    Icons/matrix.png
