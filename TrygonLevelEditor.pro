#-------------------------------------------------
#
# Project created by QtCreator 2012-11-05T20:41:59
#
#-------------------------------------------------

QT       += widgets
QT       += core gui
QT       += opengl

TARGET = TrygonLevelEditor
TEMPLATE = app

include(qtpropertybrowser/src/qtpropertybrowser.pri)

SOURCES += main.cpp\
    MainWindow.cpp \
    Model/ItemNode.cpp \
    Model/Frame.cpp \
    Model/Sprite.cpp \
    Model/Animation.cpp \
    Model/ResourceManager.cpp \
    Model/Image.cpp \
    Model/LevelProperties.cpp \
    Model/TileLayer.cpp \
    Model/Exporter.cpp \
    Model/Exporters/PackedBinaryExporter.cpp \
    Model/Commands/ModifyTilesCommand.cpp \
    Model/Commands/AddResourceCommand.cpp \
    Model/Commands/DeleteResourceCommand.cpp \
    Toolbox/ResourceView.cpp \
    Toolbox/PropertyBrowser.cpp \
    Toolbox/MiniMap.cpp \
    Toolbox/TileSelectorView.cpp \
    Toolbox/TileSelectorScene.cpp \
    Toolbox/ImageListWidgetItem.cpp \
    Toolbox/TileWidgetItem.cpp \
    LevelEditor/LayerManager.cpp \
    LevelEditor/Brushes/TileBrush.cpp \
    LevelEditor/Brushes/PencilBrush.cpp \
    LevelEditor/Brushes/FillBrush.cpp \
    LevelEditor/Brushes/SmartBrush.cpp \
    LevelEditor/Brushes/EraserBrush.cpp \
    LevelEditor/Brushes/BrushManager.cpp \
    LevelEditor/Brushes/ScatterBrush.cpp \
    LevelEditor/Brushes/ComplexBrush.cpp \
    LevelEditor/Brushes/StampBrush.cpp \
    LevelEditor/Brushes/LineBrush.cpp \
    LevelEditor/Brushes/MatrixBrush.cpp \
    LevelEditor/Brushes/ReplacerBrush.cpp \
    LevelEditor/TileLayerView.cpp \
    Dialogs/ImageViewerDialog.cpp \
    Dialogs/LayerPropertiesDialog.cpp \
    Dialogs/BrushPropertiesDialog.cpp \
    Dialogs/LevelPropertiesDialog.cpp \
    SpriteEditor/AnimationListItem.cpp \
    SpriteEditor/SpriteEditor.cpp \
    SpriteEditor/AnimationEditor.cpp \
    SpriteEditor/FrameListItem.cpp \
    SpriteEditor/SpritesheetSelector.cpp \
    SpriteEditor/SelectionGraphicsScene.cpp \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.cpp \
    SpriteEditor/AnimationPreviewer/AnimatedLabel.cpp \
    LevelEditor/LevelView.cpp \
    LevelEditor/Brushes/SelectionBrush.cpp \
    LevelEditor/Brushes/EyedropperBrush.cpp \
    Model/Clipboard.cpp

HEADERS  += \
    MainWindow.h \
    Model/ItemNode.h \
    Model/Sprite.h \
    Model/Animation.h \
    Model/Frame.h \
    Model/ResourceManager.h \
    Model/Image.h \
    Model/Exporter.h \
    Model/LevelProperties.h \
    Model/TileLayer.h \
    Model/Exporters/PackedBinaryExporter.h \
    Model/Commands/ModifyTilesCommand.h \
    Model/Commands/AddResourceCommand.h \
    Model/Commands/DeleteResourceCommand.h \
    Toolbox/TileSelectorView.h \
    Toolbox/TileSelectorScene.h \
    Toolbox/ImageListWidgetItem.h \
    Toolbox/TileWidgetItem.h \
    Toolbox/ResourceView.h \
    Toolbox/PropertyBrowser.h \
    Toolbox/MiniMap.h \
    LevelEditor/Brushes/PencilBrush.h \
    LevelEditor/Brushes/FillBrush.h \
    LevelEditor/Brushes/SmartBrush.h \
    LevelEditor/Brushes/EraserBrush.h \
    LevelEditor/Brushes/BrushManager.h \
    LevelEditor/Brushes/ScatterBrush.h \
    LevelEditor/Brushes/ComplexBrush.h \
    LevelEditor/Brushes/ReplacerBrush.h \
    LevelEditor/Brushes/StampBrush.h \
    LevelEditor/Brushes/LineBrush.h \
    LevelEditor/Brushes/MatrixBrush.h \
    LevelEditor/TileLayerView.h \
    LevelEditor/LayerManager.h \
    LevelEditor/Brushes/TileBrush.h \
    Dialogs/LayerPropertiesDialog.h \
    Dialogs/BrushPropertiesDialog.h \
    Dialogs/ImageViewerDialog.h \
    Dialogs/LevelPropertiesDialog.h \
    SpriteEditor/AnimationListItem.h \
    SpriteEditor/SpriteEditor.h \
    SpriteEditor/AnimationEditor.h \ 
    SpriteEditor/FrameListItem.h \
    SpriteEditor/SpritesheetSelector.h \
    SpriteEditor/SelectionGraphicsScene.h \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.h \
    SpriteEditor/AnimationPreviewer/AnimatedLabel.h \
    LevelEditor/LevelView.h \
    LevelEditor/Brushes/SelectionBrush.h \
    LevelEditor/Brushes/EyedropperBrush.h \
    Model/Clipboard.h

FORMS    += \
    MainWindow.ui \
    LevelEditor/Brushes/BrushManager.ui \
    Dialogs/BrushPropertiesDialog.ui \
    Dialogs/LayerPropertiesDialog.ui \
    Dialogs/ImageViewerDialog.ui \
    Dialogs/LevelPropertiesDialog.ui \
    SpriteEditor/SpriteEditor.ui \
    SpriteEditor/AnimationEditor.ui \
    SpriteEditor/SpritesheetSelector.ui \
    SpriteEditor/AnimationPreviewer/AnimationPreviewer.ui

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
