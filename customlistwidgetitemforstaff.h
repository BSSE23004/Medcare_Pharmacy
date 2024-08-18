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

public:
    explicit CustomListWidgetItemForStaff(QString name ,QIcon profilePic, QListWidget *parent = nullptr);
    void addAttendance(QString attendance);

signals:
};

#endif // CUSTOMLISTWIDGETITEMFORSTAFF_H
