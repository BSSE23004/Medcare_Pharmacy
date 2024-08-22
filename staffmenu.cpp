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
    connect(addMember, &QPushButton::clicked, this, &StaffMenu::handleAddMemberButton);
    connect(staffList, &QListWidget::currentItemChanged, this, &StaffMenu::handlestaffList);
    connect(memberInfoButton, &QPushButton::clicked, this, &StaffMenu::handleAddingAttendance);
    connect(removeMember, &QPushButton::clicked, this, &StaffMenu::handleRemoveMember);
}


void StaffMenu::writeToJson()
{
    qDebug()<<"Writing StaffMenu to Json";
    QJsonObject rootObj;
    QJsonArray staffJsonList;
    if(staffList->count()==0){
        qDebug()<<"There is no staff member to write it to json!!";
        return;
    }
    for (int row =0 ; row < staffList->count(); ++row) {
        QJsonObject jsonObj;
        CustomListWidgetItemForStaff *staffItem =static_cast<CustomListWidgetItemForStaff *>(staffList->item(row));
        QStringList dates=staffItem->getDates();
        QStringList attendances=staffItem->getattendances();
        if(dates.count()>0){
            QJsonObject datesAndAttendances;
            for (int i = 0; i < dates.count(); ++i) {
                datesAndAttendances[dates.at(i)]=attendances.at(i);
            }
            jsonObj["Dates&Attendances"]=datesAndAttendances;
        }
        jsonObj["Name"]=staffItem->text();
        jsonObj["Pin"]=staffItem->pin;
        jsonObj["Email"]=staffItem->email;
        jsonObj["Address"]=staffItem->address;
        jsonObj["PhoneNumber"]=staffItem->phoneNumber;
        jsonObj["Icon"]=staffItem->icon().name();
        staffJsonList.append(jsonObj);
    }

    rootObj["Staff"] = staffJsonList;

    QJsonDocument saveDoc(rootObj);
    QFile fOut("Staff.json");
    if (fOut.open(QIODevice::WriteOnly)) {
        fOut.write(saveDoc.toJson(QJsonDocument::Indented));
        fOut.close();
    } else {
        qDebug() << "Unable to open file for writing. StaffMenu::writeToJson()";
    }
}

StaffMenu::~StaffMenu()
{
    qDebug()<<"Deleting StaffMenu";
    writeToJson();
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
    qDebug()<<"delete addMemberDialog";
    delete addMemberDialog;
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
