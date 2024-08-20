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
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDoubleValidator>
#include <billinputdialog.h>
#include "phonelineedit.h"
#include <salesandreports.h>

class DeliveryInputDialog : public QDialog
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QFormLayout *formLayout;
    QLineEdit *customerNameLine;
    QLineEdit *customerAddressLine;
    PhoneLineEdit *customerPhoneNumberLine;
    QPushButton *cancelButton;
    double total;
    bool okButtonClicked;
    QString order;
public:
    QPushButton *okButton;
    QPushButton *orderButton;
    DeliveryInputDialog(QWidget *parent = nullptr);
    ~DeliveryInputDialog();
    QString getName();
    QString getAddress();
    QString getPhoneNumber();
    QString getOrder();
    void setTotal(double totalPrice);
    double getTotal();
    void setOrder(const QString &newOrder);
    bool isOkButtonClicked();
    void setOkButtonClicked(bool click);

private slots:
    void accept() ;
};

#endif // DELIVERYINPUTDIALOG_H
