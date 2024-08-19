#include "customlistwidgetitemforstaff.h"


CustomListWidgetItemForStaff::CustomListWidgetItemForStaff(QString name, QString newPhoneNumber, QString newAddress, QString newEmail, QIcon profilePic, QListWidget *parent)
 : QListWidgetItem{parent}
{
    setText(name);
    setIcon(profilePic);
    phoneNumber=newPhoneNumber;
    address=newAddress;
    email=newEmail;
}

void CustomListWidgetItemForStaff::addNewAttendance(QString attendance)
{
    QDate date=QDate::currentDate();
    QString currentDate =date.toString("dd/MMM/yyyy");
    attendances.append(attendance);
    dates.append(currentDate);
}

void CustomListWidgetItemForStaff::addAttendance(QString attendance)
{
    attendances.append(attendance);
}

void CustomListWidgetItemForStaff::addDates(QString date)
{
    dates.append(date);
}
