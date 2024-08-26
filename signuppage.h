#ifndef SIGNUPPAGE_H
#define SIGNUPPAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <clickablelabel.h>

class SignUpPage : public QWidget
{
    Q_OBJECT

public:
    explicit SignUpPage(QString pageName,QWidget *parent = nullptr);
    QLineEdit *nameEdit;
    QLineEdit *emailEdit;
    QLineEdit *passwordEdit;
    QPushButton *signUpButton;
    ClickableLabel *signUp;
    QString page_name;


};

#endif // SIGNUPPAGE_H
