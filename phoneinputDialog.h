#ifndef PHONEINPUTDIALOG_H
#define PHONEINPUTDIALOG_H


#include <QWidget>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QString>
#include <QLabel>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDoubleValidator>
#include <billinputdialog.h>
#include <phonelineedit.h>
#include <salesandreports.h>

class PhoneInputDialog : public QDialog
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QFormLayout *formLayout;
    PhoneLineEdit *phoneNumberLine;
    QPushButton *cancelButton;
    QPushButton *okButton;
public:
    PhoneInputDialog(QWidget *parent = nullptr): QDialog{parent}{
        phoneNumberLine =new PhoneLineEdit(this);
        okButton =new QPushButton("Ok",this);
        cancelButton =new QPushButton("Cancel",this);
        formLayout = new QFormLayout();
        formLayout->addRow("Phone Number:", phoneNumberLine);

        buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        mainLayout = new QVBoxLayout(this);
        mainLayout->addLayout(formLayout);
        mainLayout->addLayout(buttonLayout);

        setLayout(mainLayout);
        connect(okButton, &QPushButton::clicked, this, &PhoneInputDialog::accept);
        connect(cancelButton, &QPushButton::clicked, this, &PhoneInputDialog::reject);

    }

    QString getPhoneNumber(){
        return phoneNumberLine->text();
    }
private slots:
    void accept(){
        QDialog::accept();
    }
};



#endif // PHONEINPUTDIALOG_H
