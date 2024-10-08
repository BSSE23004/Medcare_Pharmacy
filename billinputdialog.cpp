#include "billInputDialog.h"



BillInputDialog::BillInputDialog(QWidget *parent)
    : QDialog{parent}
{
    addMoreButtonClicked =false;
    okButtonClicked =false;
    intValidator =new QIntValidator(this);
    doubleValidator =new QDoubleValidator(this);
    nameLine =new QLineEdit(this);
    mgLine =new QLineEdit(this);
    quantityLine =new QLineEdit(this);
    companyLine =new QLineEdit(this);
    okButton =new QPushButton("Ok",this);
    cancelButton =new QPushButton("Cancel",this);
    addMoreButton =new QPushButton("Add More",this);
    formLayout = new QFormLayout();
    formLayout->addRow("Medicine:", nameLine);
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

void BillInputDialog::setName(const QString &newName)
{
    nameLine->setText(newName);
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
    return addMoreButtonClicked;
}

bool BillInputDialog::isOkButtonClicked()
{
    return okButtonClicked;
}

void BillInputDialog::setIntValidatorRange(int start, int end)
{
    intValidator->setRange(start,end);
    mgLine->setValidator(intValidator);
}

void BillInputDialog::setDoubleValidatorRange(double start, double end)
{
    doubleValidator->setRange(start,end);
    quantityLine->setValidator(doubleValidator);
}

void BillInputDialog::setCompanyLine(QString text)
{
    companyLine->setText(text);
}

void BillInputDialog::accept()
{
    QDialog::accept();
    okButtonClicked=true;

}

void BillInputDialog::handleAddMoreButton()
{
    QDialog::accept();
    addMoreButtonClicked=true;
}




