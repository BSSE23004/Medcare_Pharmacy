#ifndef DELIVERYINPUTDIALOG_H
#define DELIVERYINPUTDIALOG_H

#include <QWidget>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QString>
#include <QLabel>
#include <QIntValidator>
#include <QDoubleValidator>



class DeliveryInputDialog : public QDialog
{
    Q_OBJECT
    QIntValidator *intValidator;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QFormLayout *formLayout;
    QLineEdit *customerNameLine;
    QLineEdit *customerAddressLine;
    QLineEdit *customerPhoneNumberLine;
    QLineEdit *orderLine;
    QPushButton *okButton;
    QPushButton *cancelButton;
public:
    DeliveryInputDialog(QWidget *parent = nullptr);
    ~DeliveryInputDialog();
    QString getName();
    QString getAddress();
    QString getPhoneNumber();
    QString getOrder();
private slots:
    void accept();
};

#endif // DELIVERYINPUTDIALOG_H
