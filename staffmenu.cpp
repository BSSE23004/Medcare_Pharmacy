#include "staffmenu.h"

StaffMenu::StaffMenu(QWidget *parent)
    : QWidget{parent}
{

    buttonsLayout =new QVBoxLayout();
    mainLayout =new QHBoxLayout(this);
    addMember =new QPushButton(QIcon(":/add.ico"),"Add Member",this);
    removeMember =new QPushButton(QIcon(":/removeButton.ico"),"Remove Member",this);
    staffList= new QListWidget(this);
    memberInfoTable= new QTableWidget(0,2,this);
    //setting Size
    staffList->setMaximumSize(200,600);
    staffList->setMinimumSize(200,600);
    memberInfoTable->setMaximumSize(600,600);
    memberInfoTable->setMinimumSize(600,600);
    addMember->setMaximumSize(270,100);
    addMember->setMinimumSize(270,100);
    removeMember->setMinimumSize(270,100);
    removeMember->setMaximumSize(270,100);
    staffList->setIconSize(QSize(60,70));
    staffList->setFont(QFont("Times New Roman",16));
    memberInfoTable->setColumnWidth(0,298);
    memberInfoTable->setColumnWidth(1,298);
    //Styling
    addMember->setFont(QFont("Times New Roman",16));
    removeMember->setFont(QFont("Times New Roman",16));
    addMember->setIconSize(QSize(60,60));
    removeMember->setIconSize(QSize(50,50));
    addMember->setStyleSheet("QPushButton {"
                               "border-radius: 10px;"  // Adjust the radius value to control how round the corners are
                               "color: green;"  // Optional: sets the text color
                               "padding: 5px 10px;"  // Optional: sets padding to make the button size more appropriate
                               "}");
    removeMember->setStyleSheet("QPushButton {"
                               "border-radius: 10px;"  // Adjust the radius value to control how round the corners are
                               "color: red;"  // Optional: sets the text color
                               "padding: 5px 10px;"  // Optional: sets padding to make the button size more appropriate
                               "}");
    QStringList headers ={"Date","Attendance"};
    memberInfoTable->setHorizontalHeaderLabels(headers);

    // setting Layout
    mainLayout->addWidget(staffList);
    mainLayout->addWidget(memberInfoTable);
    buttonsLayout->addWidget(addMember);
    buttonsLayout->addWidget(removeMember);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
    //connection
    connect(addMember,SIGNAL(clicked(bool)),this,SLOT(handleAddMemberButton()));
}

void StaffMenu::readFromJson()
{
    // QJsonObject jsonObj;
    // QDate date=QDate::currentDate();
    // QString currentDate =date.toString("dd/MMM/yyyy");
    // // Read existing data from Customers.json
    // QJsonArray dateArray;
    // QFile fIn("Staff.json");
    // if (fIn.open(QIODevice::ReadOnly)) {
    //     QByteArray jsonData = fIn.readAll();
    //     fIn.close();

    //     QJsonParseError parseError;
    //     QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
    //     if (parseError.error != QJsonParseError::NoError) {
    //         qDebug() << "Parse error: " << parseError.errorString()<<"  In addAttendance()";

    //     }

    //     if (jsonDoc.isObject()) {
    //         jsonObj = jsonDoc.object();
    //         if (jsonObj.contains(currentDate) && jsonObj[currentDate].isArray()) {
    //             dateArray =jsonObj[currentDate].toArray();
    //         } else {
    //             qDebug() << "Invalid JSON structure.In addAttendance()";

    //         }
    //     } else {
    //         qDebug() << "JSON is not an object.In addAttendance()";
    //     }
    // } else {
    //     qDebug() << "Unable to open file.In addAttendance()";
    // }
    // for (auto keys : jsonObj.keys()) {
    //     CustomListWidgetItemForStaff
    //     QJsonArray jsonArray=jsonObj[keys].toArray();
    //     for (int i = 0; i < jsonArray.count(); ++i) {
    //         if(jsonArray[i].toObject()["Name"].toString()==this->text()){
    //             attendances.append(jsonArray[i].toObject()["Attendance"].toString());
    //             phoneNumber =jsonArray[i].toObject()["PhoneNumber"].toString();
    //             email =jsonArray[i].toObject()["Email"].toString();
    //         }
    //     }
    // }

}

void StaffMenu::handleAddMemberButton()
{
    AddMemberDialog *addMemberDialog =new AddMemberDialog(this);
    if(addMemberDialog->exec()==QDialog::Accepted){
        CustomListWidgetItemForStaff *staffItem=new CustomListWidgetItemForStaff(addMemberDialog->getName(),
                                                                                  addMemberDialog->getPhoneNumber(),
                                                                                  addMemberDialog->getAddress(),
                                                                                  addMemberDialog->getEmail(),
                                                                                  QIcon(QFileDialog::getOpenFileName(this,"Choose a .jpeg/.ico File","C://")),
                                                                                  staffList);
        staffList->addItem(staffItem);
    }
}
