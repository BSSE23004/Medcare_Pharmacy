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
#include <billinputdialog.h>


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
    QPushButton *cancelButton;
    double total;
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

private slots:
    void accept();
};

#endif // DELIVERYINPUTDIALOG_H
