#ifndef BrushManager_H
#define BrushManager_H

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
#include "StampBrush.h"
#include "SelectionBrush.h"

namespace Ui {
class BrushManager;
}

class BrushManager : public QFrame
{
    Q_OBJECT
    
public:
    explicit BrushManager(QWidget *parent = 0);
    ~BrushManager();

    TileBrush *GetCurrentBrush() { return currentBrush; }

    void RepopulateBrushLists();

    void RegisterTileSelector(QGraphicsScene *selector) { propertiesWindow.RegisterTileSelector(selector); }
    void RegisterResourceManager(ResourceManager *newRM) { propertiesWindow.RegisterResourceManager(newRM); }

    void DestroyBrushes();

    enum
    {
        Pencil = 0,
        Bucket,
        Eraser,
        Line = 10,
        Stamp = 12,
        Selector = 13,
        Scatter = 6,
        Smart = 7,
        ScatterFill = 8,
        Replacer = 9,
        Matrix = 11
    };

public slots:
    void SetCurrentBrush(int type);

private slots:

    void SetSelectedTiles(TileList newList);

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
    void BrushChanged(TileBrush *newBrush, QCursor newCursor);

private:
    Ui::BrushManager *ui;
    BrushPropertiesWindow propertiesWindow;

    TileBrush *currentBrush;
    PencilBrush pencil;
    EraserBrush eraser;
    FillBrush bucket;
    LineBrush line;
    StampBrush stamp;
    SelectionBrush selector;

    QList<ScatterBrush*> scatter;
    int scatterBrushIndex;

    QList<SmartBrush*> smart;
    int smartBrushIndex;

    QList<ReplacerBrush*> replacer;
    int replacerBrushIndex;

    QList<MatrixBrush*> matrix;
    int matrixBrushIndex;
};

#endif // BrushManager_H
