#ifndef ADDMEMBERDIALOG_H
#define ADDMEMBERDIALOG_H

#include <QWidget>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QString>
#include <QLabel>
#include <phonelineedit.h>
#include <emailLineEdit.h>
#include <QIntValidator>

class AddMemberDialog : public QDialog
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QFormLayout *formLayout;
    QLineEdit *nameLine;
    PhoneLineEdit *phoneNumberLine;
    EmailLineEdit *emailLine;
    QLineEdit *addressLine;
    QIntValidator *intvalidator;
    QLineEdit *pin;
    QPushButton *okButton;
    QPushButton *cancelButton;
public:
    AddMemberDialog(QWidget *parent = nullptr);
    QString getName();
    QString getEmail();
    QString getPhoneNumber();
    QString getAddress();
    int getPin();
private slots:
    void accept();
};

#endif // ADDMEMBERDIALOG_H
