#include "custompushbutton.h"

CustomPushButton::CustomPushButton(QIcon icon, QString label, QString newCorrespondingOrder, bool newPhysical, QWidget *parent)
    : QPushButton(parent), correspondingOrder(newCorrespondingOrder)
{
    physical=newPhysical;
    buttonLabel =label;
    setText(label);
    setIcon(icon);
    setIconSize(QSize(50, 40));
    connect(this, &QPushButton::clicked, this, &CustomPushButton::handleButton);
}

void CustomPushButton::handleButton()
{
    QPixmap *customIcon;
    QMessageBox msgBox;
    customIcon= new QPixmap(":/delivery-bike.ico");
    if(physical)
        customIcon= new QPixmap(":/user.ico");
    QPixmap scaledIcon = customIcon->scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    msgBox.setIconPixmap(scaledIcon);
    msgBox.setText(correspondingOrder);
    msgBox.setWindowTitle("Information");
    msgBox.setWindowIcon(QIcon(":/cash.ico"));
    msgBox.exec();
}
