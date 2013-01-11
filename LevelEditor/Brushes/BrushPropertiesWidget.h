#ifndef BRUSHPROPERTIESWIDGET_H
#define BRUSHPROPERTIESWIDGET_H

#include <QFrame>
#include <QTime>

#include "BrushPropertiesWindow.h"

#include "TileBrush.h"
#include "PencilBrush.h"
#include "EraserBrush.h"
#include "FillBrush.h"
#include "LineBrush.h"
#include "SmartBrush.h"
#include "ScatterBrush.h"
#include "ReplacerBrush.h"
#include "MatrixBrush.h"

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

    void RegisterTileSelector(QGraphicsScene *selector) { propertiesWindow.RegisterTileSelector(selector); }
    void RegisterResourceManager(ResourceManager *newRM) { propertiesWindow.RegisterResourceManager(newRM); }

    void DestroyBrushes();
    
private slots:

    void on_overwriteCheckbox_toggled(bool checked);

    void on_brushSizeInput_valueChanged(int arg1);

    void on_addScatterBrush_clicked();

    void on_scatterBrushCombo_currentIndexChanged(int index);

    void on_editScatterBrush_clicked();

    void on_deleteScatterBrush_clicked();

    void on_smartBrushCombo_currentIndexChanged(int index);

    void on_addSmartBrush_clicked();

    void on_editSmartBrushes_clicked();

    void on_addReplacerBrush_clicked();

    void on_editReplacerBrush_clicked();

    void on_deleteReplacerBrush_clicked();

    void on_replacerBrushCombo_currentIndexChanged(int index);

    void on_addMatrixBrush_clicked();

    void on_editMatrixBrush_clicked();

    void on_deleteMatrixBrush_clicked();

    void on_matrixBrushCombo_currentIndexChanged(int index);

signals:
    void BrushChanged();

private:
    Ui::BrushPropertiesWidget *ui;
    BrushPropertiesWindow propertiesWindow;

    TileBrush *currentBrush;
    PencilBrush pencil;
    EraserBrush eraser;
    FillBrush bucket;
    LineBrush line;

    QList<ScatterBrush*> scatter;
    int scatterBrushIndex;

    QList<SmartBrush*> smart;
    int smartBrushIndex;

    QList<ReplacerBrush*> replacer;
    int replacerBrushIndex;

    QList<MatrixBrush*> matrix;
    int matrixBrushIndex;
};

#endif // BRUSHPROPERTIESWIDGET_H
