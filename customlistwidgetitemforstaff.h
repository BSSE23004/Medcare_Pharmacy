#ifndef CUSTOMLISTWIDGETITEMFORSTAFF_H
#define CUSTOMLISTWIDGETITEMFORSTAFF_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDate>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


class CustomListWidgetItemForStaff : public QListWidgetItem
{
    Q_OBJECT
    QStringList dates;
    QStringList attendances;
    QString phoneNumber;
    QString address;
    QString email;

public:
    explicit CustomListWidgetItemForStaff(QString name ,QString newPhoneNumber,QString newAddress,QString newEmail,QIcon profilePic, QListWidget *parent = nullptr);
    void addNewAttendance(QString attendance);
    void addAttendance(QString attendance);
    void addDates(QString date);

signals:
};

#endif // CUSTOMLISTWIDGETITEMFORSTAFF_H
