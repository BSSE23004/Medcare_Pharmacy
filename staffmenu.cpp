#include "staffmenu.h"

StaffMenu::StaffMenu(QWidget *parent)
    : QWidget{parent}
{

    buttonsLayout =new QVBoxLayout();
    mainLayout =new QHBoxLayout(this);
    addMember =new QPushButton(QIcon(":/add.ico"),"Add Member",this);
    removeMember =new QPushButton(QIcon(":/removeButton.ico"),"Remove Member",this);
    memberInfoButton =new QPushButton(QIcon(":/user.ico"),"Member Info",this);
    staffList= new QListWidget(this);
    memberInfoTable= new QTableWidget(0,2,this);
    //setting Size
    staffList->setMaximumSize(200,600);
    staffList->setMinimumSize(200,600);
    memberInfoTable->setMaximumSize(350,600);
    memberInfoTable->setMinimumSize(350,600);
    addMember->setMaximumSize(270,100);
    addMember->setMinimumSize(270,100);
    removeMember->setMinimumSize(270,100);
    removeMember->setMaximumSize(270,100);
    memberInfoButton->setMinimumSize(400,100);
    memberInfoButton->setMaximumSize(400,100);
    staffList->setIconSize(QSize(60,70));
    staffList->setFont(QFont("Times New Roman",16));
    memberInfoTable->setColumnWidth(0,170);
    memberInfoTable->setColumnWidth(1,157);
    memberInfoTable->setIconSize(QSize(50,50));
    memberInfoTable->setFont(QFont("Times New Roman",14));
    //Styling
    addMember->setFont(QFont("Times New Roman",16));
    removeMember->setFont(QFont("Times New Roman",16));
    memberInfoButton->setFont(QFont("Times New Roman",16));
    addMember->setIconSize(QSize(60,60));
    removeMember->setIconSize(QSize(50,50));
    memberInfoButton->setIconSize(QSize(50,50));
    addMember->setStyleSheet("QPushButton {"
                               "border-radius: 10px;"
                               "color: green;"
                               "padding: 5px 10px;"
                               "}");
    removeMember->setStyleSheet("QPushButton {"
                               "border-radius: 10px;"
                               "color: red;"
                               "padding: 5px 10px;"
                               "}");
    memberInfoButton->setStyleSheet("QPushButton {"
                               "border-radius: 10px;"
                               "color: CornflowerBlue;"
                               "padding: 5px 10px;"
                               "}");
    QStringList headers ={"Date","Attendance"};
    memberInfoTable->setHorizontalHeaderLabels(headers);

    // setting Layout
    mainLayout->addWidget(staffList);
    mainLayout->addWidget(memberInfoTable);
    buttonsLayout->addWidget(memberInfoButton);
    buttonsLayout->addWidget(addMember);
    buttonsLayout->addWidget(removeMember);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);
    //connection
    connect(addMember,SIGNAL(clicked(bool)),this,SLOT(handleAddMemberButton()));
    connect(staffList,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(handlestaffList()));
    connect(memberInfoButton,SIGNAL(clicked(bool)),this,SLOT(handleAddingAttendance()));
    connect(removeMember,SIGNAL(clicked(bool)),this,SLOT(handleRemoveMember()));
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
    addMemberDialog->setMinimumWidth(300);
    if(addMemberDialog->exec()==QDialog::Accepted){
        CustomListWidgetItemForStaff *staffItem=new CustomListWidgetItemForStaff(addMemberDialog->getName(),
                                                                                  addMemberDialog->getPhoneNumber(),
                                                                                  addMemberDialog->getAddress(),
                                                                                  addMemberDialog->getEmail(),
                                                                                   addMemberDialog->getPin(),
                                                                                  QIcon(QFileDialog::getOpenFileName(this,"Choose a .jpeg/.ico File","C://")),
                                                                                  staffList);
        staffList->addItem(staffItem);
    }
}

void StaffMenu::handlestaffList()
{
    memberInfoTable->setRowCount(0);
    if(staffList->count()==0){
        QMessageBox::warning(this,"Warning","There is none in the members list");
        return;
    }
    CustomListWidgetItemForStaff *staffItem =static_cast<CustomListWidgetItemForStaff *>(staffList->currentItem());
    for (int i = 0; i < staffItem->getDates().count(); ++i) {
        memberInfoTable->setRowCount(memberInfoTable->rowCount()+1);
        memberInfoTable->setRowHeight(memberInfoTable->rowCount()-1,50);
        QTableWidgetItem *item =new QTableWidgetItem(QIcon(":/calender.ico"),staffItem->getDates().at(i));
        item->setFlags(item->flags()& ~Qt::ItemIsEditable);
        memberInfoTable->setItem(memberInfoTable->rowCount()-1,0,item);
        item =new QTableWidgetItem(QIcon(":/attended.ico"),staffItem->getattendances().at(i));
        item->setFlags(item->flags()& ~Qt::ItemIsEditable);
        memberInfoTable->setItem(memberInfoTable->rowCount()-1,1,item);
    }
    memberInfoButton->setIcon(staffItem->icon());
    memberInfoButton->setText("Email : "+staffItem->email+"\nPhone : "+staffItem->phoneNumber+"\nAddress : "+staffItem->address);
}

void StaffMenu::handleAddingAttendance()
{
    memberInfoTable->setRowCount(0);
    if(staffList->count()==0){
        QMessageBox::warning(this,"Warning","There is none in the members list so whose attendance you want to mark!!");
        return;
    }
    CustomListWidgetItemForStaff *staffItem =static_cast<CustomListWidgetItemForStaff *>(staffList->currentItem());
    int pin =QInputDialog::getInt(this,"Pin","Enter pin for attendance : ");
    if(pin==staffItem->pin){
        staffItem->addNewAttendance("Present");
    }else {
        QMessageBox::warning(this,"Warning","Entered Wrong Pin!!!");

    }
    for (int i = 0; i < staffItem->dates.count(); ++i) {
        memberInfoTable->setRowCount(memberInfoTable->rowCount()+1);
        memberInfoTable->setRowHeight(memberInfoTable->rowCount()-1,50);
        QTableWidgetItem *item =new QTableWidgetItem(QIcon(":/calender.ico"),staffItem->getDates().at(i));
        item->setFlags(item->flags()& ~Qt::ItemIsEditable);
        memberInfoTable->setItem(memberInfoTable->rowCount()-1,0,item);
        item =new QTableWidgetItem(QIcon(":/attended.ico"),staffItem->getattendances().at(i));
        item->setFlags(item->flags()& ~Qt::ItemIsEditable);
        memberInfoTable->setItem(memberInfoTable->rowCount()-1,1,item);
    }
}

void StaffMenu::handleRemoveMember()
{
    if(staffList->count()==0){
        QMessageBox::warning(this,"Warning","There is none in the members list");
        return;
    }
    if(staffList->count()==1){
        QMessageBox::warning(this,"Warning","You can't delete last member \n at least one member is must!!!");
        return;
    }
    QString email = QInputDialog::getText(this,"Email Box","Enter his Email : ");
    for (int i = 0; i < staffList->count(); ++i) {
        CustomListWidgetItemForStaff *staffItem =static_cast<CustomListWidgetItemForStaff *>(staffList->item(i));
        if(email==staffItem->email){
            delete staffList->takeItem(i);
            return;
        }
    }
    QMessageBox::warning(this,"Warning","No Member listed with this Email");
}
