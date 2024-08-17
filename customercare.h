#ifndef CUSTOMERCARE_H
#define CUSTOMERCARE_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QByteArray>
#include <customlistwidgetitem.h>

class CustomerCare : public QWidget
{
    Q_OBJECT
    int aw;
    int ah;
    int ax;
    int ay;
    QListWidget *customersList;
    QPushButton *detailButton;
public:
    explicit CustomerCare(QWidget *parent = nullptr);
    void initializeList();
    ~CustomerCare();

private slots:
    void handleListWidget();
};

#endif // CUSTOMERCARE_H
