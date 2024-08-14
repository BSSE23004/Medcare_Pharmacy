#ifndef CUSTOMPUSHBUTTON_H
#define CUSTOMPUSHBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QIcon>
#include <QString>
#include <QMessageBox>

class CustomPushButton : public QPushButton
{
    Q_OBJECT
public:
    QString correspondingOrder;
    bool physical;
    QString buttonLabel;
    CustomPushButton(QIcon icon, QString label, QString newCorrespondingOrder,bool newPhysical, QWidget *parent = nullptr);

private slots:
    void handleButton();

};

#endif // CUSTOMPUSHBUTTON_H

