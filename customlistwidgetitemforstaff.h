#ifndef CUSTOMLISTWIDGETITEMFORSTAFF_H
#define CUSTOMLISTWIDGETITEMFORSTAFF_H

#include <QWidget>
#include <QListWidgetItem>
#include <QDate>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QObject>


class CustomListWidgetItemForStaff : public QListWidgetItem
{
    Q_OBJECT
    QStringList dates;
    QStringList attendances;

public:
    QString phoneNumber;
    QString address;
    QString email;
    int pin;
    explicit CustomListWidgetItemForStaff(QString name ,QString newPhoneNumber,QString newAddress,QString newEmail,int newPin,QIcon profilePic, QListWidget *parent = nullptr);
    void addNewAttendance(QString attendance);
    void addAttendance(QString attendance);
    void addDates(QString date);
    QStringList getDates();
    QStringList getattendances();

signals:
};

#endif // CUSTOMLISTWIDGETITEMFORSTAFF_H
