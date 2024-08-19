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
// #include <phonelineedit.h>

class AddMemberDialog : public QDialog
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QFormLayout *formLayout;
    QLineEdit *nameLine;
    QLineEdit *phoneNumberLine;
    QLineEdit *emailLine;
    QLineEdit *addressLine;
    QPushButton *okButton;
    QPushButton *cancelButton;
public:
    AddMemberDialog(QWidget *parent = nullptr);
    QString getName();
    QString getEmail();
    QString getPhoneNumber();
    QString getAddress();
private slots:
    void accept();
};

#endif // ADDMEMBERDIALOG_H
