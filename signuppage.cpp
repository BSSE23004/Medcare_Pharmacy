#include "SignUpPage.h"
#include <QMessageBox>
#include <QFont>
#include <QPalette>
#include <QColor>

SignUpPage::SignUpPage(QString pageName, QWidget *parent) : QWidget(parent)
{
    page_name=pageName;
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(50, 50, 50, 50);
    QLabel *titleLabel;
    if(pageName=="Login"){
        titleLabel = new QLabel("Login Now!!!", this);
    }
    else {
        titleLabel = new QLabel("Signup Now!!!", this);
    }
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    if(pageName=="Signup"){
        nameEdit = new QLineEdit(this);
        nameEdit->setPlaceholderText("Enter your name");
        mainLayout->addWidget(nameEdit);
    }

    emailEdit = new QLineEdit(this);
    emailEdit->setPlaceholderText("Enter your email");
    mainLayout->addWidget(emailEdit);


    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Enter your password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(passwordEdit);

    if(pageName=="Login"){
        signUpButton = new QPushButton("Login", this);
    }
    else {
        signUpButton = new QPushButton("Signup", this);
    }
    signUpButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px;");
    mainLayout->addWidget(signUpButton);
    if(pageName=="Login"){
        QHBoxLayout *registrationLayout =new QHBoxLayout();
        QLabel *question= new QLabel("Haven't registered yet?",this);
        signUp= new ClickableLabel("Signup Now",this);
        signUp->setStyleSheet("QLabel { color: blue; text-decoration: underline; }");
        registrationLayout->addWidget(question);
        registrationLayout->addWidget(signUp);
        mainLayout->addLayout(registrationLayout);
    }


    QPalette palette;
    palette.setColor(QPalette::Window, QColor("#f5f5f5"));
    setAutoFillBackground(true);
    setPalette(palette);
}


