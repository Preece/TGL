#ifndef PACKEDBINARYEXPORTER_H
#define PACKEDBINARYEXPORTER_H

#include "../Exporter.h"

class PackedBinaryExporter : public Exporter
{
public:
    PackedBinaryExporter();

    //these functions help write out different types of data
    /*bool WriteType(int ID, QString type);
    bool WriteString(QString string);
    bool WriteInt(int number);
    bool WriteDouble(double number);
    bool WriteBool(bool boolean);
    bool WriteRect(QRect rect);
    bool WritePoint(QPoint point);
    bool WriteImage(QImage image);
    bool WriteVariant(QVariant var);

    //these functions help read in different types of data
    bool ReadType(int &ID, QString name);
    bool ReadString(QString &string);
    bool ReadInt(int &number);
    bool ReadDouble(double &number);
    bool ReadBool(bool &boolean);
    bool ReadRect(QRect &rect);
    bool ReadPoint(QPoint &point);
    bool ReadImage(QImage &image);
    bool ReadVariant(QVariant var);*/
};

#endif // PACKEDBINARYEXPORTER_H
