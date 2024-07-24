#include "inputdialog.h"

InputDialog::InputDialog(QWidget *parent)
    : QDialog{parent}
{
    nameLine =new QLineEdit(this);
    mgLine =new QLineEdit(this);
    quantityLine =new QLineEdit(this);
    priceLine =new QLineEdit(this);
    companyLine =new QLineEdit(this);
    okButton =new QPushButton("Ok",this);
    cancelButton =new QPushButton("Cancel",this);
    formLayout = new QFormLayout();
    intValidator=new QIntValidator(this);
    doubleValidator =new QDoubleValidator(this);
    mgLine->setValidator(intValidator);
    quantityLine->setValidator(doubleValidator);
    formLayout->addRow("Name:", nameLine);
    formLayout->addRow("Price:", priceLine);
    formLayout->addRow("Quantity:", quantityLine);
    formLayout->addRow("MG:", mgLine);
    formLayout->addRow("Company:", companyLine);

    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(okButton, &QPushButton::clicked, this, &InputDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &InputDialog::reject);
}

QString InputDialog::getName()
{
    return nameLine->text();
}

QString InputDialog::getPrice()
{
    return priceLine->text();
}

QString InputDialog::getmg()
{
    return mgLine->text();
}

QString InputDialog::getQuantity()
{
    return quantityLine->text();
}

QString InputDialog::getCompany()
{
    return companyLine->text();
}

InputDialog::~InputDialog()
{
    delete mainLayout;
    delete buttonLayout;
    delete formLayout;
    delete nameLine;
    delete priceLine;
    delete mgLine;
    delete quantityLine;
    delete companyLine;
    delete okButton;
    delete cancelButton;
    delete intValidator;
    delete doubleValidator;
}

void InputDialog::accept()
{
    QDialog::accept();
}

