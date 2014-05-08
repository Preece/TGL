#ifndef OBJECTPROPERTY_H
#define OBJECTPROPERTY_H

#include <QVariant>
#include <QString>

class ObjectProperty
{
public:
    ObjectProperty();
    ObjectProperty(QString newName, QVariant newValue, bool newInh);
    ObjectProperty(bool newInh);

    void SetName(QString newName) { name = newName; }
    QString GetName() { return name; }

    void SetValue(QVariant newValue) { value = newValue; }
    QVariant GetValue() { return value; }
    QVariant::Type GetType() { return value.type(); }

    bool IsInherent() { return inherent; }
    void SetInherent(bool newInherentValue) { inherent = newInherentValue; }

private:
    QVariant value;
    QString name;

    bool inherent;
};

#endif // OBJECTPROPERTY_H
