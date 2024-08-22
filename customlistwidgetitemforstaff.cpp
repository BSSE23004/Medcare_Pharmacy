#include "customlistwidgetitemforstaff.h"


void CustomListWidgetItemForStaff::setDates(const QStringList &newDates)
{
    dates = newDates;
}

void CustomListWidgetItemForStaff::setAttendances(const QStringList &newAttendances)
{
    attendances = newAttendances;
}

CustomListWidgetItemForStaff::CustomListWidgetItemForStaff(QString name, QString newPhoneNumber, QString newAddress, QString newEmail, int newPin, QString profilePic, QListWidget *parent)
 : QListWidgetItem{parent}
{
    iconName=profilePic;
    QIcon profile(iconName);
    setText(name);
    setIcon(profile);
    pin=newPin;
    phoneNumber=newPhoneNumber;
    address=newAddress;
    email=newEmail;
}

void CustomListWidgetItemForStaff::addNewAttendance(QString attendance)
{
    QDate date=QDate::currentDate();
    QString currentDate =date.toString("dd/MMM/yyyy");
    if(dates.contains(currentDate)){
        return;
    }
    attendances.append(attendance);
    dates.append(currentDate);
}

void CustomListWidgetItemForStaff::addAttendance(QString attendance)
{
    attendances.append(attendance);
}

void CustomListWidgetItemForStaff::addDates(QString date)
{
    if(dates.contains(date)){
        return;
    }
    dates.append(date);
}

QStringList CustomListWidgetItemForStaff::getDates()
{
    return dates;
}

QStringList CustomListWidgetItemForStaff::getattendances()
{
    return attendances;
}
