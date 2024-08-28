#include "sliderdialog.h"

SliderDialog::SliderDialog(QWidget *parent): QDialog{parent}{
    slider=new QSlider(Qt::Horizontal);
    slider->setRange(0,100);
    slider->setSingleStep(1);
    formLayout =new QFormLayout();
    formLayout->addRow(slider);

    buttonLayout =new QHBoxLayout();
    okButton =new QPushButton("Ok",this);
    cancelButton =new QPushButton("Cancel",this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
    connect(okButton, &QPushButton::clicked, this, &SliderDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &SliderDialog::reject);


}




void SliderDialog::accept()
{
    QDialog::accept();
}
