#include "profilemenu.h"

ProfileMenu::ProfileMenu(QWidget *parent, QString newEmail)
    : QWidget{parent}
{
    iconName="";
    mainLayout = new QHBoxLayout(this);
    contactBoardLayout = new QVBoxLayout();
    contactImageLayout = new QHBoxLayout();
    contactDetailsLayout = new QVBoxLayout();
    settingButtonsLayout = new QVBoxLayout();

    QWidget *contactBoardWidget = new QWidget(this);
    contactBoardWidget->setLayout(contactBoardLayout);

    contactBoardWidget->setGeometry(0,0,300, 200);
    contactBoardWidget->setFixedSize(650, 450);


    contactBoardWidget->setStyleSheet("QWidget {"
                                      "background-color: gainsboro;"
                                      "color: black;"
                                      "border: none;"
                                      "border-radius: 10px;"
                                      "padding: 10px;"
                                      "}"
                                      "QPushButton, QLabel {"
                                      "border: none;"
                                      "}");


    contactInfoHeader = new QLabel("Contact Info");
    QFont titleFont;
    titleFont.setFamily("Times New Roman");
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    contactInfoHeader->setFont(titleFont);
    contactInfoHeader->setAlignment(Qt::AlignCenter);

    addImage = new QPushButton(QIcon(":/add-image.ico"), "Add Image");
    addImage->setIconSize(QSize(100, 200));
    addImage->setFont(QFont("Times New Roman",16));
    addImage->setFixedSize(QSize(300,350));
    qDebug()<<"New Email "<<newEmail;
    email = new QPushButton(QIcon(":/email.ico"), newEmail);
    email->setIconSize(QSize(50, 50));
    email->setFont(QFont("Times New Roman",16));
    email->setFixedSize(QSize(300,150));

    addPhoneNumber = new QPushButton(QIcon(":/phone.ico"), "Add phone");
    addPhoneNumber->setIconSize(QSize(50, 50));
    addPhoneNumber->setFont(QFont("Times New Roman",16));
    addPhoneNumber->setFixedSize(QSize(300,150));

    setWindowsOpacity =new QPushButton(QIcon(":/setting.ico"),"Set Opacity");
    setWindowsOpacity->setIconSize(QSize(50, 50));
    setWindowsOpacity->setFont(QFont("Times New Roman",16));
    setWindowsOpacity->setFixedSize(QSize(300,150));
    setWindowsOpacity->setStyleSheet("QPushButton {"
                                     "border-radius: 10px;"
                                     "padding: 5px 10px;"
                                     "}");
    setWindowsFont =new QPushButton(QIcon(":/setting.ico"),"Set Font");
    setWindowsFont->setIconSize(QSize(50, 50));
    setWindowsFont->setFont(QFont("Times New Roman",16));
    setWindowsFont->setFixedSize(QSize(300,150));
    setWindowsFont->setStyleSheet("QPushButton {"
                                     "border-radius: 10px;"
                                     "padding: 5px 10px;"
                                     "}");

    clock =new QPushButton(QIcon(":/clock.ico"),"");
    clock->setIconSize(QSize(50, 50));
    clock->setFont(QFont("Times New Roman",16));
    clock->setFixedSize(QSize(300,150));
    clock->setStyleSheet("QPushButton {"
                                  "border-radius: 10px;"
                                  "padding: 5px 10px;"
                                  "}");


    contactBoardLayout->addWidget(contactInfoHeader);
    contactImageLayout->addWidget(addImage);
    contactDetailsLayout->addWidget(email);
    contactDetailsLayout->addWidget(addPhoneNumber);
    contactImageLayout->addLayout(contactDetailsLayout);
    contactBoardLayout->addLayout(contactImageLayout);
    settingButtonsLayout->addWidget(clock);
    settingButtonsLayout->addWidget(setWindowsOpacity);
    settingButtonsLayout->addWidget(setWindowsFont);


    mainLayout->addWidget(contactBoardWidget);
    mainLayout->addLayout(settingButtonsLayout);

    setLayout(mainLayout);
    connect(addPhoneNumber,&QPushButton::clicked,this,&ProfileMenu::handlePhoneNumber);
    connect(addImage,&QPushButton::clicked,this,&ProfileMenu::handleProfilePic);
    connect(email,&QPushButton::clicked,this,&ProfileMenu::handleEmail);
    QTimer *timer=new QTimer(this);
    connect(timer,&QTimer::timeout,this,&ProfileMenu::handleClock);
    timer->start(1000);
    readFromJson();
}

ProfileMenu::~ProfileMenu()
{
    writeToJson();
}

void ProfileMenu::writeToJson()
{
    QJsonObject jsonObj;
    QFile file("Credentials.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString();
            return;
        }

        if (jsonDoc.isObject()) {
            jsonObj = jsonDoc.object();
        } else {
            qDebug() << "JSON is not an object.";
            return;
        }
    } else {
        qDebug() << "Unable to open file.";
        return;
    }
    jsonObj["PhoneNumber"]=addPhoneNumber->text();
    jsonObj["ProfilePic"]=iconName;
    QJsonDocument jsonDoc(jsonObj);
    QFile fOut("Credentials.json");
    if (fOut.open(QIODevice::WriteOnly)) {
        fOut.write(jsonDoc.toJson(QJsonDocument::Indented));
        fOut.close();
    } else {
        qDebug() << "Unable to open Credentials.json file for writing.";
    }
}

void ProfileMenu::readFromJson(){
    QJsonObject jsonObj;
    QFile file("Credentials.json");
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray jsonData = file.readAll();
        file.close();

        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "Parse error: " << parseError.errorString();
            return;
        }

        if (jsonDoc.isObject()) {
            jsonObj = jsonDoc.object();
        } else {
            qDebug() << "JSON is not an object.";
            return;
        }
    } else {
        qDebug() << "Unable to open file.";
        return;
    }
    if(jsonObj.contains("ProfilePic")&&jsonObj.contains("PhoneNumber")){
    addImage->setIcon(QIcon(jsonObj["ProfilePic"].toString()));
    addImage->setText("");
    addImage->setIconSize(QSize(300,350));
    addPhoneNumber->setText(jsonObj["PhoneNumber"].toString());
    }
}

void ProfileMenu::handlePhoneNumber()
{
    if(addPhoneNumber->text()=="Add phone"){
        PhoneInputDialog *phoneInput=new PhoneInputDialog(this);
        if(phoneInput->exec()==QDialog::Accepted){
            if(phoneInput->getPhoneNumber()==""){
                QMessageBox::warning(this,"Invalid Input","Enter complete data!!!");
                return;
            }
            addPhoneNumber->setText(phoneInput->getPhoneNumber());
        }
    }
}

void ProfileMenu::handleProfilePic()
{
    if(addImage->text()=="Add Image"){
        iconName=QFileDialog::getOpenFileName(this,"Choose a .jpeg/.ico File","C://");
        addImage->setIcon(QIcon(iconName));
        addImage->setText("");
        addImage->setIconSize(QSize(300,350));
    }
}

void ProfileMenu::handleEmail()
{
    QDesktopServices::openUrl(QUrl("mailto:"+email->text()));
}

void ProfileMenu::handleClock()
{
    QTime time=QTime::currentTime();
    QString text=time.toString("hh:mm ap");
    if(time.second()%2==0){
        text[2]=' ';
    }
    clock->setText(text);
}
