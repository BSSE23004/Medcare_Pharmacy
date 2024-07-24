#ifndef BILLINPUTDIALOG_H
#define BILLINPUTDIALOG_H

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

class BillInputDialog : public QDialog
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QFormLayout *formLayout;
    QLineEdit *nameLine;
    QLineEdit *mgLine;
    QLineEdit *quantityLine;
    QLineEdit *companyLine;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QPushButton *addMoreButton;
    QIntValidator *intValidator;
    QDoubleValidator *doubleValidator;
    bool clicked;
public:
    explicit BillInputDialog(QWidget *parent = nullptr);
    QString getName();
    QString getmg();
    QString getQuantity();
    QString getCompany();
    bool isAddMoreButtonClicked();
    ~BillInputDialog();
private slots:
    void accept();
    void handleAddMoreButton();
};

#endif // BILLINPUTDIALOG_H
