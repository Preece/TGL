#ifndef BRUSHPROPERTIESWINDOW_H
#define BRUSHPROPERTIESWINDOW_H

#include <QDialog>
#include <QGraphicsScene>

#include "../../Model/ResourceManager.h"

#include "ScatterBrush.h"

namespace Ui {
class BrushPropertiesWindow;
}

class BrushPropertiesWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit BrushPropertiesWindow(QWidget *parent = 0);
    ~BrushPropertiesWindow();

    void RegisterTileSelector(QGraphicsScene *selector);
    void RegisterResourceManager(ResourceManager *newRM) { resourceManager = newRM; }

    void NewScatterBrush(ScatterBrush *newBrush);
    void EditScatterBrush(ScatterBrush *editBrush);
    
private:
    Ui::BrushPropertiesWindow *ui;

    ResourceManager *resourceManager;

    QGraphicsScene tileList;

    ScatterBrush *currentScatterBrush;
};

#endif // BRUSHPROPERTIESWINDOW_H
