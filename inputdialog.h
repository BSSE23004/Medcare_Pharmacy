#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QIntValidator>
#include <QDoubleValidator>
class InputDialog : public QDialog
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QFormLayout *formLayout;
    QLineEdit *nameLine;
    QLineEdit *priceLine;
    QLineEdit *mgLine;
    QLineEdit *quantityLine;
    QLineEdit *companyLine;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QIntValidator *intValidator;
    QDoubleValidator *doubleValidator;
public:
    explicit InputDialog(QWidget *parent = nullptr);
    QString getName();
    QString getPrice();
    QString getmg();
    QString getQuantity();
    QString getCompany();
    ~InputDialog();

private slots:
    void accept();
};

#endif // INPUTDIALOG_H
