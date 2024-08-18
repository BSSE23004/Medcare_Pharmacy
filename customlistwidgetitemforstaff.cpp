#include "customlistwidgetitemforstaff.h"

CustomListWidgetItemForStaff::CustomListWidgetItemForStaff(QString name, QIcon profilePic, QListWidget *parent)
    : QListWidgetItem{parent}
{
    QJsonObject jsonObj;
    QDate date=QDate::currentDate();
    QString currentDate =date.toString("dd/MMM/yyyy");
    setText(name);
    setIcon(profilePic);
    // Read existing data from Customers.json
    QJsonArray dateArray;
    QFile fIn("Staff.json");
    if (fIn.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = fIn.readAll();
        fIn.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString()<<"  In addAttendance()";

        }

        if (jsonDoc.isObject()) {
            jsonObj = jsonDoc.object();
            if (jsonObj.contains(currentDate) && jsonObj[currentDate].isArray()) {
                dateArray =jsonObj[currentDate].toArray();
            } else {
                qDebug() << "Invalid JSON structure.In addAttendance()";

            }
        } else {
            qDebug() << "JSON is not an object.In addAttendance()";
        }
    } else {
        qDebug() << "Unable to open file.In addAttendance()";
    }
    for (auto keys : jsonObj.keys()) {
        dates.append(keys);
        QJsonArray jsonArray=jsonObj[keys].toArray();
        for (int i = 0; i < jsonArray.count(); ++i) {
            if(jsonArray[i].toObject()["Name"].toString()==this->text()){
                attendances.append(jsonArray[i].toObject()["Attendance"].toString());
            }
        }
    }
}

void CustomListWidgetItemForStaff::addAttendance(QString attendance)
{
    QDate date=QDate::currentDate();
    QString currentDate =date.toString("dd/MMM/yyyy");
    attendances.append(attendance);
    dates.append(currentDate);



}
