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
    Model/ResourceController.cpp \
    Model/ResourceNode.cpp \
    Model/Image.cpp \
    Model/LevelProperties.cpp \
    Model/TileLayer.cpp \
    Model/Clipboard.cpp \
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
    LevelEditor/Brushes/TileBrush.cpp \
    LevelEditor/Brushes/PencilBrush.cpp \
    LevelEditor/Brushes/FillBrush.cpp \
    LevelEditor/Brushes/SmartBrush.cpp \
    LevelEditor/Brushes/EraserBrush.cpp \
    LevelEditor/Brushes/BrushController.cpp \
    LevelEditor/Brushes/ScatterBrush.cpp \
    LevelEditor/Brushes/ComplexBrush.cpp \
    LevelEditor/Brushes/StampBrush.cpp \
    LevelEditor/Brushes/LineBrush.cpp \
    LevelEditor/Brushes/MatrixBrush.cpp \
    LevelEditor/Brushes/ReplacerBrush.cpp \
    Dialogs/ImageViewerDialog.cpp \
    Dialogs/BrushPropertiesDialog.cpp \
    LevelEditor/Brushes/SelectionBrush.cpp \
    LevelEditor/Brushes/EyedropperBrush.cpp \   
    Toolbox/LayerListView.cpp \
    LevelEditor/TileScene.cpp \
    LevelEditor/TileLayerItem.cpp \
    LevelEditor/TileView.cpp \
    Model/TileController.cpp \
    Exporters/Exporter.cpp \
    Exporters/JSONExporter.cpp

HEADERS  += \
    MainWindow.h \
    Model/Image.h \
    Model/LevelProperties.h \
    Model/TileLayer.h \
    Model/Clipboard.h \
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
    LevelEditor/Brushes/BrushController.h \
    LevelEditor/Brushes/ScatterBrush.h \
    LevelEditor/Brushes/ComplexBrush.h \
    LevelEditor/Brushes/ReplacerBrush.h \
    LevelEditor/Brushes/StampBrush.h \
    LevelEditor/Brushes/LineBrush.h \
    LevelEditor/Brushes/MatrixBrush.h \
    LevelEditor/Brushes/TileBrush.h \
    Dialogs/BrushPropertiesDialog.h \
    Dialogs/ImageViewerDialog.h \
    LevelEditor/Brushes/SelectionBrush.h \
    LevelEditor/Brushes/EyedropperBrush.h \   
    Toolbox/LayerListView.h \
    LevelEditor/TileView.h \
    LevelEditor/TileLayerItem.h \
    LevelEditor/TileScene.h \
    Model/ResourceNode.h \
    Model/ResourceController.h \
    Model/TileController.h \
    Exporters/Exporter.h \
    Exporters/JSONExporter.h

FORMS    += \
    MainWindow.ui \
    LevelEditor/Brushes/BrushController.ui \
    Dialogs/BrushPropertiesDialog.ui \
    Dialogs/ImageViewerDialog.ui \

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
