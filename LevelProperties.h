#ifndef LEVELPROPERTIES_H
#define LEVELPROPERTIES_H

#include <QDialog>

namespace Ui {
class LevelProperties;
}

class LevelProperties : public QDialog
{
    Q_OBJECT
    
public:
    explicit LevelProperties(QWidget *parent = 0);
    ~LevelProperties();
    
private:
    Ui::LevelProperties *ui;
};

#endif // LEVELPROPERTIES_H
