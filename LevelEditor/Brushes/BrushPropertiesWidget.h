#ifndef BRUSHPROPERTIESWIDGET_H
#define BRUSHPROPERTIESWIDGET_H

#include <QFrame>

#include "BrushPropertiesWindow.h"

#include "TileBrush.h"
#include "PencilBrush.h"
#include "EraserBrush.h"
#include "FillBrush.h"
#include "SmartBrush.h"
#include "ScatterBrush.h"

namespace Ui {
class BrushPropertiesWidget;
}

class BrushPropertiesWidget : public QFrame
{
    Q_OBJECT
    
public:
    explicit BrushPropertiesWidget(QWidget *parent = 0);
    ~BrushPropertiesWidget();

    void SetSelectedTileID(int newID);

    void SetCurrentBrush(int type);
    TileBrush *GetCurrentBrush() { return currentBrush; }

    void RepopulateBrushLists();
    
private slots:

    void on_overwriteCheckbox_toggled(bool checked);

    void on_brushSizeInput_valueChanged(int arg1);

    void on_addScatterBrush_clicked();

private:
    Ui::BrushPropertiesWidget *ui;
    BrushPropertiesWindow *propertiesWindow;

    TileBrush *currentBrush;
    PencilBrush pencil;
    EraserBrush eraser;
    FillBrush bucket;

    QList<ScatterBrush*> scatter;
};

#endif // BRUSHPROPERTIESWIDGET_H
