#include "deliveryinputdialog.h"



void DeliveryInputDialog::setOrder(const QString &newOrder)
{
    order = newOrder;
}

DeliveryInputDialog::DeliveryInputDialog(QWidget *parent): QDialog{parent} {
    total=0;
    intValidator =new QIntValidator(this);
    customerNameLine =new QLineEdit(this);
    customerAddressLine =new QLineEdit(this);
    customerPhoneNumberLine =new QLineEdit(this);
    customerPhoneNumberLine->setValidator(intValidator);
    okButton =new QPushButton("Ok",this);
    cancelButton =new QPushButton("Cancel",this);
    orderButton =new QPushButton("Order",this);
    formLayout = new QFormLayout();
    formLayout->addRow("Name:", customerNameLine);
    formLayout->addRow("Address:", customerAddressLine);
    formLayout->addRow("Phone Number:", customerPhoneNumberLine);


    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(orderButton);
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
    delete intValidator;
    delete customerNameLine;
    delete customerAddressLine;
    delete customerPhoneNumberLine;
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
    return order;
}

void DeliveryInputDialog::setTotal(double totalPrice)
{
    total=totalPrice;
}

double DeliveryInputDialog::getTotal()
{
    return total;
}

void DeliveryInputDialog::accept()
{
    QDialog::accept();
}


