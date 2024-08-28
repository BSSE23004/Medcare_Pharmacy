#ifndef SLIDERDIALOG_H
#define SLIDERDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>


class SliderDialog : public QDialog
{
    Q_OBJECT
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QFormLayout *formLayout;
    QPushButton *okButton;
    QPushButton *cancelButton;
public:
    QSlider *slider;
    SliderDialog(QWidget *parent);

private slots:
    void accept() ;

};

#endif // SLIDERDIALOG_H