#include "addmemberdialog.h"

AddMemberDialog::AddMemberDialog(QWidget *parent) : QDialog{parent} {

    nameLine =new QLineEdit(this);
    addressLine =new QLineEdit(this);
    emailLine =new EmailLineEdit(this);
    intvalidator =new QIntValidator(this);
    pin =new EmailLineEdit(this);
    pin->setValidator(intvalidator);
    phoneNumberLine =new PhoneLineEdit(this);
    okButton =new QPushButton("Ok",this);
    cancelButton =new QPushButton("Cancel",this);
    formLayout = new QFormLayout();
    formLayout->addRow("Name:", nameLine);
    formLayout->addRow("Phone:", phoneNumberLine);
    formLayout->addRow("Email:", emailLine);
    formLayout->addRow("Address:", addressLine);
    formLayout->addRow("Pin:", pin);


    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(okButton, &QPushButton::clicked, this, &AddMemberDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &AddMemberDialog::reject);
}

QString AddMemberDialog::getName()
{
    return nameLine->text();
}


QString AddMemberDialog::getEmail()
{
    return emailLine->text();
}

QString AddMemberDialog::getPhoneNumber()
{
    return phoneNumberLine->text();
}

QString AddMemberDialog::getAddress()
{
    return addressLine->text();
}

int AddMemberDialog::getPin()
{
    return pin->text().toInt();
}

void AddMemberDialog::accept()
{
    QDialog::accept();
}
