#include "billInputDialog.h"



BillInputDialog::BillInputDialog(QWidget *parent)
    : QDialog{parent}
{
    clicked =false;
    intValidator =new QIntValidator(this);
    doubleValidator =new QDoubleValidator(this);
    nameLine =new QLineEdit(this);
    mgLine =new QLineEdit(this);
    quantityLine =new QLineEdit(this);
    companyLine =new QLineEdit(this);
    okButton =new QPushButton("Ok",this);
    cancelButton =new QPushButton("Cancel",this);
    addMoreButton =new QPushButton("Add More",this);
    mgLine->setValidator(intValidator);
    quantityLine->setValidator(doubleValidator);
    formLayout = new QFormLayout();
    formLayout->addRow("Name:", nameLine);
    formLayout->addRow("Quantity:", quantityLine);
    formLayout->addRow("MG:", mgLine);
    formLayout->addRow("Company:", companyLine);


    buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addMoreButton);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(okButton, &QPushButton::clicked, this, &BillInputDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &BillInputDialog::reject);
    connect(addMoreButton, &QPushButton::clicked, this, &BillInputDialog::handleAddMoreButton);
    connect(nameLine, &QLineEdit::textChanged, this, &BillInputDialog::nameTextChanged);
}

QString BillInputDialog::getName()
{
    return nameLine->text();
}

QString BillInputDialog::getmg()
{
    return mgLine->text();
}

QString BillInputDialog::getQuantity()
{
    return quantityLine->text();
}

QString BillInputDialog::getCompany()
{
    return companyLine->text();
}

bool BillInputDialog::isAddMoreButtonClicked()
{
    return clicked;
}

BillInputDialog::~BillInputDialog()
{
    delete mainLayout;
    delete buttonLayout;
    delete formLayout;
    delete nameLine;
    delete mgLine;
    delete quantityLine;
    delete companyLine;
    delete okButton;
    delete cancelButton;
    delete addMoreButton;
    delete intValidator;
    delete doubleValidator;
}



void BillInputDialog::accept()
{
    QDialog::accept();
}

void BillInputDialog::handleAddMoreButton()
{
    QDialog::accept();
    clicked=true;
}




