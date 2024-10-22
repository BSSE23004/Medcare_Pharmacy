#include "deliveryinputdialog.h"



void DeliveryInputDialog::setOrder(const QString &newOrder)
{
    order = newOrder;
}

bool DeliveryInputDialog::isOkButtonClicked()
{
    return okButtonClicked;
}

void DeliveryInputDialog::setOkButtonClicked(bool click)
{
    okButtonClicked=click;
}


DeliveryInputDialog::DeliveryInputDialog(QWidget *parent): QDialog{parent} {
    okButtonClicked=false;
    total=0;
    customerNameLine =new QLineEdit(this);
    customerAddressLine =new QLineEdit(this);
    customerPhoneNumberLine =new PhoneLineEdit(this);
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


