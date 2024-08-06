#include "deliveryinputdialog.h"



DeliveryInputDialog::DeliveryInputDialog(QWidget *parent): QDialog{parent} {
    intValidator =new QIntValidator(this);
    customerNameLine =new QLineEdit(this);
    customerAddressLine =new QLineEdit(this);
    customerPhoneNumberLine =new QLineEdit(this);
    orderLine =new QLineEdit(this);
    customerPhoneNumberLine->setValidator(intValidator);
    okButton =new QPushButton("Ok",this);
    cancelButton =new QPushButton("Cancel",this);
    formLayout = new QFormLayout();
    formLayout->addRow("Name:", customerNameLine);
    formLayout->addRow("Address:", customerAddressLine);
    formLayout->addRow("Phone Number:", customerPhoneNumberLine);
    formLayout->addRow("Order:", orderLine);


    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(okButton, &QPushButton::clicked, this, &DeliveryInputDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &DeliveryInputDialog::reject);

}

DeliveryInputDialog::~DeliveryInputDialog()
{
    delete mainLayout;
    delete buttonLayout;
    delete formLayout;
    delete okButton;
    delete cancelButton;
}

QString DeliveryInputDialog::getName()
{
    return customerNameLine->text();
}

QString DeliveryInputDialog::getAddress()
{
    return customerAddressLine->text();
}

QString DeliveryInputDialog::getPhoneNumber()
{
    return customerPhoneNumberLine->text();
}

QString DeliveryInputDialog::getOrder()
{
    return orderLine->text();
}

void DeliveryInputDialog::accept()
{
    QDialog::accept();
}
