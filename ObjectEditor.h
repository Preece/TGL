#ifndef OBJECTEDITOR_H
#define OBJECTEDITOR_H

#include <QDialog>

namespace Ui {
class ObjectEditor;
}

class ObjectEditor : public QDialog
{
    Q_OBJECT
    
public:
    explicit ObjectEditor(QWidget *parent = 0);
    ~ObjectEditor();
    
private:
    Ui::ObjectEditor *ui;
};

#endif // OBJECTEDITOR_H
