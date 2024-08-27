#include "profilemenu.h"

ProfileMenu::ProfileMenu(QWidget *parent, QString newEmail)
    : QWidget{parent}
{
    mainLayout = new QHBoxLayout(this);
    contactBoardLayout = new QVBoxLayout();
    contactImageLayout = new QHBoxLayout();
    contactDetailsLayout = new QVBoxLayout();

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


    // Setting up labels and buttons
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



    // Adding widgets to layouts
    contactBoardLayout->addWidget(contactInfoHeader);
    contactImageLayout->addWidget(addImage);
    contactDetailsLayout->addWidget(email);
    contactDetailsLayout->addWidget(addPhoneNumber);
    contactImageLayout->addLayout(contactDetailsLayout);
    contactBoardLayout->addLayout(contactImageLayout);

    // Adding the contact board widget to the main layout
    mainLayout->addWidget(contactBoardWidget);

    setLayout(mainLayout);
    connect(addPhoneNumber,&QPushButton::clicked,this,&ProfileMenu::handlePhoneNumber);
    connect(addImage,&QPushButton::clicked,this,&ProfileMenu::handleProfilePic);
    connect(email,&QPushButton::clicked,this,&ProfileMenu::handleEmail);
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
    addImage->setIcon(QIcon(QFileDialog::getOpenFileName(this,"Choose a .jpeg/.ico File","C://")));
    addImage->setText("");
    addImage->setIconSize(QSize(300,350));
}

void ProfileMenu::handleEmail()
{
    QDesktopServices::openUrl(QUrl("mailto:"+email->text()));
}
